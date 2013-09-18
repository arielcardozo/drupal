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
 
class OfferEntity implements OfferEntityInterface {
 
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
 

  public function getUid() {
    return $this->uid;
  }
 
  public function setUid($uid) {
    $this->uid = $uid;
  }

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

  public function getUid();
 
  public function setUid($uid);

  public function getFecha_creacion();

  public function setFecha_creacion($fecha_creacion);

  public function setObra_musical($obra_musical);

  public function getObra_musical();

  public function getSalon();

  public function setSalon($salon);

  public function getPiano();

  public function setPiano($piano);

  public function getInstrumento_autor();

  public function setInstrumento_autor($instrumento_autor);

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

  const UID = 'uid';
  
  const FECHA_CREACION = 'fecha_creacion';

  const DISPONIBILIDAD = 'disponibilidad';

  const SALON = 'salon';

  const PIANO = 'piano';

  const INSTRUMENTO_AUTOR = 'instrumento_autor';

  const CIUDAD = 'ciudad';

  const ACTIVO = 'activo';

  const ID = 'nid_oferta';

  const OFFERS_TABLE_NAME = 'pym_ofertas';
 
  protected $uid;
  protected $fecha_creacion;
  protected $obra_musical;
  protected $autor_obra;
  protected $salon;
  protected $piano;
  protected $instrumento_autor;
  protected $ciudad;
  protected $disponibilidad;
  protected $activo;
  protected $key;

  protected $user_name;
  protected $user_mail;
 
  public static function create() {
    return new Offer();
  }

  public function getUid(){
    return $this->uid;
  }
 
  public function setUid($uid) {
    $this->uid = $uid;
    return $this;
  }

  public function getFecha_creacion(){
    return $this->fecha_creacion;
  }

  public function setFecha_creacion($fecha_creacion) {
    $this->fecha_creacion = $fecha_creacion;
    return $this;
  }

public function getObra_musical(){
    return $this->obra_musical;
  }

  public function setObra_musical($obra_musical) {
    $this->obra_musical = $obra_musical;
    return $this;
  }


 public function getAutor_obra()
 {
    return $this->autor_obra;
  }
 
  public function setAutor_obra($autor_obra) {
    $this->autor_obra = $autor_obra;
    return $this;
  }

  public function getUser_name()
 {
    return $this->user_name;
  }
 
  public function setUser_name($user_name) {
    $this->user_name = $user_name;
    return $this;
  }
  public function getUser_mail()
 {
    return $this->user_mail;
  }
 
  public function setUser_mail($user_mail) {
    $this->user_mail = $user_mail;
    return $this;
  }



  public function getSalon(){
    return $this->salon;
  }

  public function setSalon($salon) {
    $this->salon = $salon;
    return $this;
  }

  public function getPiano(){
    return $this->piano;
  }

  public function setPiano($piano) {
    $this->piano = $piano;
    return $this;
  }

  public function getInstrumento_autor(){
    return $this->instrumento_autor;
  }

  public function setInstrumento_autor($instrumento_autor) {
    $this->instrumento_autor = $instrumento_autor;
    return $this;
  }

  public function getCiudad(){
    return $this->ciudad;
  }

  public function setCiudad($ciudad) {
    $this->ciudad = $ciudad;
    return $this;
  }

 
  public function getActivo(){
    return $this->activo;
  }
 
  public function setActivo($activo) {
    $this->activo = $activo;
    return $this;
  }

  public function getDisponibilidad(){
    return $this->disponibilidad;
  }
 
  public function setDisponibilidad($disponibilidad) {
    $this->disponibilidad = $disponibilidad;
    return $this;
  }


  public function toArray() {
    return array('obra_musical' => $this->obra_musical,
        'autor_obra' => $this->autor_obra,
        'uid' => $this->uid,
        'disponibilidad' =>$this->disponibilidad,
        'salon' =>$this->salon,
        'piano' =>$this->piano,
        'instrumento_autor' =>$this->instrumento_autor,
        'ciudad' =>$this->ciudad,
        'user_name'=>$this->user_name,
        'user_mail' =>$this->user_mail,
        'activo' =>$this->activo,
        'fecha_creacion' =>$this->fecha_creacion,);
  }
 
}
 
class DbOffer {
 

  //Obtiene un oferta
  function get($id) {
    try {
        $fields = array(Offer::ID,
          Offer::UID,
          Offer::AUTOR_OBRA,
          Offer::OBRA_MUSICAL,
          Offer::FECHA_CREACION,
          Offer::SALON,
          Offer::PIANO,
          Offer::INSTRUMENTO_AUTOR,
          Offer::CIUDAD,
          Offer::DISPONIBILIDAD,
          Offer::ACTIVO);
 
      $oferta = db_select(Offer::OFFERS_TABLE_NAME, 'n')
                      ->fields('n', $fields)
                      ->condition(Offer::ID, $id);
      $oferta->addField('u', 'name','name');
      $oferta->addField('u', 'mail','mail');
      $oferta->leftJoin('users', 'u', 'u.uid = n.uid ');               
      $result = $oferta->execute()->fetch();
      $offer = new Offer();
      $offer->setKey($result->nid_oferta);
      $offer->setObra_musical($result->obra_musical);
      $offer->setAutor_obra($result->autor_obra);
      $offer->setUid($result->uid);
      $offer->setFecha_creacion($result->fecha_creacion);
      $offer->setSalon($result->salon);
      $offer->setPiano($result->piano);
      $offer->setInstrumento_autor($result->instrumento_autor);
      $offer->setUser_name($result->name);
      $offer->setCiudad($result->ciudad);
      $offer->setUser_mail($result->mail);
      $offer->setDisponibilidad($result->disponibilidad);
      $offer->setActivo($result->activo);
    } catch (Exception $e) {
      $databaseException = new OfferDatabaseException($e->getMessage(), 'Get Folk Record',
                      t('Index ID: @index', array('@index' => $id)), TRUE);
      $databaseException->handle();
    }
    return $offer;
  }
 
 //Obtiene listado de ofertas
  function getOfferList($header) {
    try {
        $fields = array(Offer::ID,
          Offer::UID,
          Offer::AUTOR_OBRA,
          Offer::OBRA_MUSICAL,
          Offer::FECHA_CREACION,
          Offer::SALON,
          Offer::PIANO,
          Offer::INSTRUMENTO_AUTOR,
          Offer::CIUDAD,
          Offer::DISPONIBILIDAD,
          Offer::ACTIVO);
 
      $oferta = db_select(Offer::OFFERS_TABLE_NAME, 'n')
                      ->fields('n', $fields);
                      //->condition(Offer::ID, $id);
      $oferta->addField('u', 'name','name');
      $oferta->addField('u', 'mail','mail');
      $oferta->leftJoin('users', 'u', 'u.uid = n.uid ');   
      $oferta = $oferta->extend('PagerDefault')->limit(20); // line1
      $oferta = $oferta->extend('TableSort');
      $result = $oferta->orderByHeader($header)->execute()->fetchAll();            
      //$result = $oferta->execute()->fetchAll();


      
    } catch (Exception $e) {
      $databaseException = new OfferDatabaseException($e->getMessage(), 'Get Folk Record',
                      t('Index ID: @index', array('@index' => $id)), TRUE);
      $databaseException->handle();
    }
    return $result;
  }
  //Añade una oferta
  function add($uid,$autor_obra, $obra_musical,$fecha_creacion,$salon,$piano,$instrumento_autor,$ciudad,$disponibilidad,$activo) {
    $id_oferta = 0;
    try {
      $fields = array(
          Offer::UID,
          Offer::AUTOR_OBRA,
          Offer::OBRA_MUSICAL,
          Offer::FECHA_CREACION,
          Offer::INSTRUMENTO_AUTOR,
          Offer::SALON,
          Offer::PIANO,
          Offer::CIUDAD,
          Offer::DISPONIBILIDAD,
          Offer::ACTIVO);
 
      $insert = db_insert(Offer::OFFERS_TABLE_NAME)->fields($fields);
      $insert->values(array($uid, $autor_obra,$obra_musical,$fecha_creacion,$instrumento_autor,$salon,$piano,$ciudad,$disponibilidad,$activo));
      $id_oferta = $insert->execute();
    } catch (Exception $e) {
      $databaseException = new OfferDatabaseException($e->getMessage(), 'Add',
                      t('Obra Musical: @obra_musical, Autor Obra: @autor_obra, Fecha de creación: @fecha_creacion', 
                           array('@obra_musical' => $obra_musical,
                          '@autor_obra' => $autor_obra,'@fecha_creacion' => $fecha_creacion)), TRUE);
      $databaseException->handle();
    }
    return $id_oferta;
  }
 
  //Establece valores o actualiza
  function set(OfferInterface $offer) {
    try {
      $query = db_update('pym_ofertas');
      $query->condition('nid_oferta', $offer->getKey(), '=');
      $query->fields(array(
          'obra_musical' => $offer->getObra_musical(),
          'autor_obra' => $offer->getAutor_obra(),
          'instrumento_autor'=> $offer->getInstrumento_autor(),
          'disponibilidad' => $offer->getDisponibilidad(),
          'salon' => $offer->getSalon(),
          'piano' => $offer->getPiano(),
          'ciudad' => $offer->getCiudad(),
      ));
      $query->execute();
    } catch (Exception $e) {
      $databaseException = new OfferDatabaseException($e->getMessage(), 'Update',
                      t('Offer Id: @id', array('@id' => $offer->getKey())), TRUE);
      $databaseException->handle();
    }
  }
 
 //Establece valores o actualiza
  function deleteAutor_instrument($id) {
    try {
      $query = db_update('pym_ofertas');
      $query->condition('nid_oferta', $id, '=');
      $query->fields(array(
           'instrumento_autor'=> 1,
      ));
      $query->execute();
    } catch (Exception $e) {
      $databaseException = new OfferDatabaseException($e->getMessage(), 'Update',
                      t('Offer Id: @id', array('@id' => $offer->getKey())), TRUE);
      $databaseException->handle();
    }
  }
  //Elimina una entrada de instrumento
  function delete($id) {
    try {
      $query = db_delete('pym_ofertas');
      $query->condition('nid_oferta', $id, '=');
      $query->execute();
    } catch (Exception $e) {
      $databaseException = new OfferDatabaseException($e->getMessage(),
                      'Delete', t('Offer Id: @id', array('@id' => $id)), TRUE);
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