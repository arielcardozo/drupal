<?php
<?php

/**
 * @file
 * Provides Features integration for entity types using the CRUD API.
 */

interface OfferEntityInterface {
 
  public function getObraMusical();
 
  public function setObraMusical($obra_musical);
 
  public function getKey();
 
  public function setKey($key);
}
 
class OfferEntity implements InstrumentEntityInterface {
 
  protected $uid;
  protected $fecha_creacion;
  protected $obra_musical;
  protected $autor_obra;
  protected $salon;
  protected $piano;
  protected $ciudad;
  protected $disponibilidad;
  protected $activo;
  protected $key;
 
  public function getFechaCreacion() {
    return $this->fecha_creacion;
  }
 
  public function setFechaCreacion($fecha_creacion) {
    $this->fecha_creacion = $fecha_creacion;
  }

   public function getObraMusical() {
    return $this->obra_musical;
  }
 
  public function setObraMusical($obra_musical) {
    $this->obra_musical = $obra_musical;
  }

   public function getAutorObra() {
    return $this->autor_obra;
  }
 
  public function setAutorObra($autor_obra) {
    $this->autor_obra = $autor_obra;
  }

  public function getSalon() {
    return $this->salon;
  }
 
  public function setSalon($salon) {
    $this->salon = $salon;
  }

  public function getPiano() {
    return $this->piano;
  }
 
  public function setPiano($piano) {
    $this->piano = $piano;
  }

  public function getCiudad() {
    return $this->ciudad;
  }
 
  public function setCiudad($ciudad) {
    $this->ciudad = $ciudad;
  }

  public function getDisponibilidad() {
    return $this->disponibilidad;
  }
 
  public function setDisponibilidad($disponibilidad) {
    $this->disponibilidad = $disponibilidad;
  } 

  public function getActivo() {
    return $this->activo;
  }
 
  public function setActivo($activo) {
    $this->activo = $activo;
  }  
  public function getKey() {
    return $this->key;
  }
 
  public function setKey($index) {
    $this->key = $index;
  }
 
}
 
 
interface OfferInterface {
 
  public function getAutor_obra();
 
  public function setAutor_obra($autor_obra);

  public function getFecha_creacion();

  public function setFecha_creacion($fecha_creacion);

  public function setObra_musical($obra_musical);

  public function getObra_musical();

  public function getSalon();

  public function setSalon($salon);

  public function getPiano();

  public function setPiano($piano);

  public function getCiudad();

  public function setCiudad($ciudad);
      
  public function getActivo();
 
  public function setActivo($activo);

  public function getDisponibilidad();
 
  public function setDisponibilidad($disponibilidad);
 
}
 
class Offer extends OfferEntity implements OfferInterface {
 
  const AUTOR_OBRA = 'autor_obra';
  
  const OBRA_MUSICAL = 'obra_musical';
  
  const FECHA_CREACION = 'fecha_creacion';

  const DISPONIBILIDAD = 'disponibilidad';

  const SALON = 'salon';

  const PIANO = 'piano';

  const CIUDAD = 'ciudad';

  const ACTIVO = 'activo';

  const ID = 'nid_oferta';

  const INSTRUMENTS_TABLE_NAME = 'pym_ofertas';
 
 
  protected $obra_musical;
  protected $autor_obra;
  protected $fecha_creacion;
  protected $disponibilidad;
  protected $salon;
  protected $piano;
  protected $ciudad;
  protected $activo;
 
  public static function create() {
    return new Offer();
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
    return array('obra_musical' => $this->obra_musical,
        'autor_obra' => $this->autor_obra,
        'disponibilidad' =>$this->disponibilidad,
        'salon' =>$this->salon,
        'piano' =>$this->piano,
        'ciudad' =>$this->ciudad,
        'activo' =>$this->activo,
        'fecha_creacion' =>$this->fecha_creacion,);
  }
 
}
 
class DbOffer {
 
  //Obtiene un instrumento
  function get($id) {
    try {
      $fields = array(Offer::ID,
          Offer::AUTOR_OBRA,
          Offer::OBRA_MUSICAL,
          Offer::FECHA_CREACION,
          Offer::SALON,
          Offer::PIANO,
          Offer::CIUDAD,
          Offer::DISPONIBILIDAD,
          Offer::ACTIVO);
 
      $result = db_select(Offer::INSTRUMENTS_TABLE_NAME, 'n')
                      ->fields('n', $fields)
                      ->condition(Offer::ID, $id)->execute()->fetch();
      $offer = new Offer();
      $offer->setKey($result->nid_oferta);
      $offer->setObra_musical($result->obra_musical);
      $offer->setAutor_obra($result->autor_obra);
      $offer->setAutor_obra($result->autor_obra);
      $offer->setAutor_obra($result->autor_obra);
      $offer->setAutor_obra($result->autor_obra);
      $offer->setAutor_obra($result->autor_obra);
      $offer->setAutor_obra($result->autor_obra);
    } catch (Exception $e) {
      $databaseException = new InstrumentDatabaseException($e->getMessage(), 'Get Folk Record',
                      t('Index ID: @index', array('@index' => $id)), TRUE);
      $databaseException->handle();
    }
    return $offer;
  }
 
  //Añade un instrumento
  function add($name_instrument, $description_instrument) {
    try {
      $fields = array(Offer::NAME_INSTRUMENT, Offer::DESCRIPTION_INSTRUMENT);
 
      $insert = db_insert(Offer::INSTRUMENTS_TABLE_NAME)->fields($fields);
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
      $query = db_update('pym_ofertas');
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
      $query = db_delete('pym_ofertas');
      $query->condition('nid_instrument', $id, '=');
      $query->execute();
    } catch (Exception $e) {
      $databaseException = new InstrumentDatabaseException($e->getMessage(),
                      'Delete', t('Instruments Id: @id', array('@id' => $id)), TRUE);
      $databaseException->handle();
    }
  }
 
}

class OfferDatabaseException extends Exception {
 
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