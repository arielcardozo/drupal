<?php

/**
 * @file
 * Provides Features integration for entity types using the CRUD API.
 */

interface InstrumentEntityInterface {
 
  public function getName();
 
  public function setName($name);
 
  public function getKey();
 
  public function setKey($key);
}
 
class InstrumentEntity implements InstrumentEntityInterface {
 
  protected $name;
  protected $description;
  protected $key;
 
  public function getName() {
    return $this->name;
  }
 
  public function setName($name) {
    $this->name = $name;
  }

   public function getDescription() {
    return $this->description;
  }
 
  public function setDescription($description) {
    $this->description = $description;
  }
 
  public function getKey() {
    return $this->key;
  }
 
  public function setKey($index) {
    $this->key = $index;
  }
 
}
 
 
interface InstrumentInterface {
 
  public function getName_instrument();
 
  public function setName_instrument($name_instrument);
 
  public function getDescription_instrument();
 
  public function setDescription_instrument($description_instrument);
 
}
 
class Instrument extends InstrumentEntity implements InstrumentInterface {
 
  const NAME_INSTRUMENT = 'name_instrument';
  const DESCRIPTION_INSTRUMENT = 'description_instrument';
  const ID = 'nid_instrument';
  const INSTRUMENTS_TABLE_NAME = 'instruments';
 
 
  protected $name_instrument;
  protected $description_instrument;
 
  public static function create() {
    return new Instrument();
  }
 
  public function getName_instrument() {
    return $this->name_instrument;
  }
 
  public function setName_instrument($name_instrument) {
    $this->name_instrument = $name_instrument;
    return $this;
  }
 
  public function getDescription_instrument() {
    return $this->description_instrument;
  }
 
  public function setDescription_instrument($description_instrument) {
    $this->description_instrument = $description_instrument;
    return $this;
  }
 
 
  public function toArray() {
    return array('name_instrument' => $this->name_instrument,
        'description_instrument' => $this->description_instrument);
  }
 
}
 
class DbInstrument {
 
  //Obtiene un instrumento
  function get($id) {
    try {
      $fields = array(Instrument::ID,
          Instrument::NAME_INSTRUMENT,
          Instrument::DESCRIPTION_INSTRUMENT);
 
      $result = db_select(Instrument::INSTRUMENTS_TABLE_NAME, 'n')
                      ->fields('n', $fields)
                      ->condition(Instrument::ID, $id)->execute()->fetch();
      $instrument = new Instrument();
      $instrument->setKey($result->nid_instrument);
      $instrument->setName_instrument($result->name_instrument);
      $instrument->setDescription_instrument($result->description_instrument);
    } catch (Exception $e) {
      $databaseException = new InstrumentDatabaseException($e->getMessage(), 'Get Folk Record',
                      t('Index ID: @index', array('@index' => $id)), TRUE);
      $databaseException->handle();
    }
    return $instrument;
  }
 
  //Añade un instrumento
  function add($name_instrument, $description_instrument) {
    try {
      $fields = array(Instrument::NAME_INSTRUMENT, Instrument::DESCRIPTION_INSTRUMENT);
 
      $insert = db_insert(Instrument::INSTRUMENTS_TABLE_NAME)->fields($fields);
      $insert->values(array($name_instrument, $description_instrument));
      $insert->execute();
    } catch (Exception $e) {
      $databaseException = new InstrumentDatabaseException($e->getMessage(), 'Add',
                      t('Instrument Name: @name_instrument, Instrument Description: @description_instrument, Color: @color', 
                           array('@name_instrument' => $name_instrument,
                          '@description_instrument' => $description_instrument)), TRUE);
      $databaseException->handle();
    }
  }
 
  //Establece valores o actualiza
  function set(InstrumentInterface $instrument) {
    try {
      $query = db_update('Instruments');
      $query->condition('nid_instrument', $instrument->getKey(), '=');
      $query->fields(array(
          'name_instrument' => $instrument->getName_instrument(),
          'description_instrument' => $instrument->getDescription_instrument())
      );
      $query->execute();
    } catch (Exception $e) {
      $databaseException = new InstrumentDatabaseException($e->getMessage(), 'Update',
                      t('Instruments Id: @id', array('@id' => $instrument->getKey())), TRUE);
      $databaseException->handle();
    }
  }
 
  //Elimina una entrada de instrumento
  function delete($id) {
    try {
      $query = db_delete('instruments');
      $query->condition('nid_instrument', $id, '=');
      $query->execute();
    } catch (Exception $e) {
      $databaseException = new InstrumentDatabaseException($e->getMessage(),
                      'Delete', t('Instruments Id: @id', array('@id' => $id)), TRUE);
      $databaseException->handle();
    }
  }
 
}

class InstrumentDatabaseException extends Exception {
 
  private $databaseOperation;
  private $operationParamenters;
  private $displayMessage;
  protected $message;
 
  function __construct($message, $databaseOperation, $operationParamenters, $displayMessage = TRUE) {
    $this->message = $message;
    $this->databaseOperation = $databaseOperation;
    $this->operationParamenters = $operationParamenters;
    $this->displayMessage = $displayMessage;
  }
 
  function handle() {
    if ($this->displayMessage) {
      $output =
              t('Database Exception : @operation : @parameters : @system', array(
          '@operation' => $this->databaseOperation,
          '@parameters' => $this->operationParamenters,
          '@system' => $this->message
              )
      );
      drupal_set_message($output, 'error');
    }
  }
 
}