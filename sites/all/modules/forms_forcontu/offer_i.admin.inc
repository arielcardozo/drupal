<?php

/**
 * @file
 * Provides Features integration for entity types using the CRUD API.
 */

interface OfferInstrumentEntityInterface {
 
  public function getNidOfertas();
  public function setNidOfertas($nid_oferta);
 
  public function getNidInstrument();
  public function setNidInstrument($nid_instrument);
 
  public function getUid();
  public function setUid($uid);

  public function getPosition();
  public function setPosition($position);
}
 
class OfferInstrumentEntity implements OfferInstrumentEntityInterface {
 
  protected $uid;
  protected $nid_oferta;
  protected $nid_instrument;
  protected $position;
  
  public function getUid() {
    return $this->uid;
  }
 
  public function setUid($uid) {
    $this->uid = $uid;
  }

  public function getNidOfertas() {
    return $this->nid_oferta;
  }
 
  public function setNidOfertas($nid_oferta) {
    $this->nid_oferta = $nid_oferta;
  }

   public function getNidInstrument() {
    return $this->nid_instrument;
  }
 
  public function setNidInstrument($nid_instrument) {
    $this->nid_instrument = $nid_instrument;
  }

   public function getPosition() {
    return $this->autor_obra;
  }
 
  public function setPosition($position) {
    $this->position = $position;
  }

  
 
}
 
 
interface OfferInstrumentInterface {
 
  public function getUid();
 
  public function setUid($uid);

  public function getNid_oferta();

  public function setNid_oferta($nid_oferta);
  
  public function getNid_instrument();
  public function setNid_instrument($nid_instrument);

  public function getPosition();

  public function setPosition($position);

   
}
 
class OfferInstrument extends OfferInstrumentEntity implements OfferInstrumentInterface {
 
  const UID = 'uid';
  
  const NID_OFERTAS = 'nid_oferta';

  const NID_INSTRUMENTS = 'nid_instrument';

  const POSITION = 'position';

  const OFFERS_TABLE_NAME = 'pym_instrumentos_ofertas';

  
 
  protected $uid;
  protected $nid_oferta;
  protected $nid_instrument;
  protected $position;
  
 
  public static function create() {
    return new OfferInstrument();
  }

  public function getUid(){
    return $this->uid;
  }
 
  public function setUid($uid) {
    $this->uid = $uid;
    return $this;
  }

  public function getNid_oferta(){
    return $this->nid_oferta;
  }

  public function setNid_oferta($nid_oferta) {
    $this->nid_oferta = $nid_oferta;
    return $this;
  }

public function getNid_instrument(){
    return $this->nid_instrument;
  }

  public function setNid_instrument($nid_instrument) {
    $this->nid_instrument = $nid_instrument;
    return $this;
  }


 public function getPosition()
 {
    return $this->position;
  }
 
  public function setPosition($position) {
    $this->position = $position;
    return $this;
  }

  

  public function toArray() {
    return array('nid_oferta' => $this->nid_oferta,
        'nid_instrument' => $this->nid_instrument,
        'uid' => $this->uid,
        'position' =>$this->position,);
  }
 
}
 
class DbOfferInstrument {
 
  //Obtiene un instrumento
  function get($id) {
    try {
        $fields = array(OfferInstrument::UID,
          OfferInstrument::NID_OFERTAS,
          OfferInstrument::NID_INSTRUMENTS,
          OfferInstrument::POSITION,
          );
 
      $result = db_select(Offer::OFFERS_TABLE_NAME, 'n')
                      ->fields('n', $fields)
                      ->condition(Offer::ID, $id)->execute()->fetch();
      $offer = new OfferInstrument();
      $offer->setNid_oferta($result->nid_oferta);
      $offer->setNid_instrument($result->nid_instrument);
      $offer->setUid($result->uid);
      $offer->setPosition($result->position);
      
    } catch (Exception $e) {
      $databaseException = new OfferDatabaseException($e->getMessage(), 'Get Folk Record',
                      t('Index ID: @index', array('@index' => $id)), TRUE);
      $databaseException->handle();
    }
    return $offer;
  }
 
  //Añade un instrumento
  function add($uid,$nid_oferta, $nid_instrument,$position) {

    /*$i=1;

    for ($i=1; $i<=$no_of_fields; $i++)
          {
              if($form_state['values']['performers'.$i]!=0){
                    $result = db_insert('pym_instrumentos_ofertas')
                ->fields(array(
                'nid_instrument' => $form_state['values']['performers'.$i],
                'nid_oferta' => $id_oferta,
                'uid'=>0,
                'position'=>$i,
                ))
                ->execute();
              
              }
        
          }*/

      try {
        $fields = array(OfferInstrument::UID,
            OfferInstrument::NID_OFERTAS,
            OfferInstrument::NID_INSTRUMENTS,
            OfferInstrument::POSITION,
            );
   
        $insert = db_insert(OfferInstrument::OFFERS_TABLE_NAME)->fields($fields);
        $insert->values(array($uid,$nid_oferta, $nid_instrument,$position));
        $id_instrument = $insert->execute();
      } catch (Exception $e) {
        $databaseException = new OfferDatabaseException($e->getMessage(), 'Add',
                        t('Oferta: @nid_oferta, Instrumento: @nid_instrument', 
                             array('@nid_oferta' => $nid_oferta,
                            '@nid_instrument' => $nid_instrument)), TRUE);
        $databaseException->handle();
      }
  }
 
  //Establece valores o actualiza
  function set(OfferInstrumentInterface $offer) {
    try {
      $query = db_update('pym_instrumentos_ofertas');
      $query->condition('nid_oferta', $offer->getKey(), '=');
      $query->fields(array(
          'uid' => $offer->getUid(),
          'nid_oferta' => $offer->getNid_oferta(),
          'nid_instrument' => $offer->getNid_instrument(),
          'position' => $offer->getPosition(),
          
      ));
      $query->execute();
    } catch (Exception $e) {
      $databaseException = new OfferDatabaseException($e->getMessage(), 'Update',
                      t('Offer Id: @id', array('@id' => $offer->getKey())), TRUE);
      $databaseException->handle();
    }
  }
 
  //Elimina una entrada de instrumento
  function delete($uid,$nid_oferta, $nid_instrument,$position) {
    try {
      $query = db_delete('pym_instrumentos_ofertas');
      $query->condition('nid_oferta', $nid_oferta, '=');
      $query->condition('nid_instrument', $nid_instrument, '=');
      $query->condition('position', $position, '=');
      $query->condition('uid', $uid, '=');
      $query->execute();
    } catch (Exception $e) {
      $databaseException = new OfferDatabaseException($e->getMessage(),
                      'Delete', t('Offer Id: @id', array('@id' => $id)), TRUE);
      $databaseException->handle();
    }
  }
 
}

class OfferInstrumentsDatabaseException extends Exception {
 
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