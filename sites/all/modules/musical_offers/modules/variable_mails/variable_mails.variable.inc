<?php
/**
 * @file
 * Variable API module. Definition for some xample variables
 */

/**
 * Implements hook_variable_info().
 */
function variable_mails_variable_info($options) {

  //Checkbox
  $variables['variable_mails_enviar_creador_creacion'] = array(
    'title' => t('Enviar mail al creador de la oferta en la creación de la oferta', array(), $options),
    'type' => 'boolean',
    'default' => TRUE,
    'group' => 'variable_mails',
  );

  // Texto para el creador
  $variables['variable_mails_offer_owner_[mail_part]'] = array(
    'type' => 'mail_text',
    'title' => t('Creación de oferta', array(), $options),
    'default' => array(
      'subject' => t('Registro de oferta enviado por @site-name', array(), $options),
      'body' => t('@name Le envía a usted un mensaje de confirmación del alta de su oferta:', array(), $options),
    ),
    'description' => t('Correo enviado al creador de la oferta.', array(), $options),
    'required' => TRUE,
    'group' => 'variable_mails',
  );

  //Checkbox
  $variables['variable_mails_enviar_admin_creacion'] = array(
    'title' => t('Enviar mail al administrador en la creación de la oferta', array(), $options),
    'type' => 'boolean',
    'default' => TRUE,
    'group' => 'variable_mails',
  );
  // Texto para el creador
  $variables['variable_mails_admin_mail_[mail_part]'] = array(
    'type' => 'mail_text',
    'title' => t('Creación de oferta', array(), $options),
    'default' => array(
      'subject' => t('Registro de oferta enviado por @user-name', array(), $options),
      'body' => t('Se acaba de crear una nueva oferta con los siguientes datos:', array(), $options),
    ),
    'description' => t('Correo enviado al administrador del sistema.', array(), $options),
    'required' => TRUE,
    'group' => 'variable_mails',
  );

  //SE REALIZA UNA SUSCRPCIÓN
  //Checkbox
  $variables['variable_mails_enviar_subscriber_suscripcion'] = array(
    'title' => t('Enviar mail al suscriptor en la suscripción a la oferta', array(), $options),
    'type' => 'boolean',
    'default' => TRUE,
    'group' => 'variable_mails',
  );
  // Texto para el suscriptor
  $variables['variable_mails_offer_subscriber_[mail_part]'] = array(
    'type' => 'mail_text',
    'title' => t('Se realiza una suscripción', array(), $options),
    'default' => array(
      'subject' => t('Registro de suscripción enviado por @site-name', array(), $options),
      'body' => t('@name Le envía a usted un mensaje de confirmación del alta de su suscripción a la oferta:', array(), $options),
    ),
    'description' => t('Correo enviado al suscriptor de una oferta al suscribirse.', array(), $options),
    'required' => TRUE,
    'group' => 'variable_mails',
  );
  //Checkbox
  $variables['variable_mails_enviar_creador_suscripcion'] = array(
    'title' => t('Enviar mail al creador de la oferta en la suscripción a la oferta', array(), $options),
    'type' => 'boolean',
    'default' => TRUE,
    'group' => 'variable_mails',
  );  
  $variables['variable_mails_subscriber_offer_owner_[mail_part]'] = array(
    'type' => 'mail_text',
    'title' => t('Se realiza una suscripción', array(), $options),
    'default' => array(
      'subject' => t('Registro de suscripción enviado por @user-name', array(), $options),
      'body' => t('@user-name Se acaba de suscribir a una de tus ofertas con los siguientes datos:', array(), $options),
    ),
    'description' => t('Correo enviado al creador de la oferta a la que se suscriben.', array(), $options),
    'required' => TRUE,
    'group' => 'variable_mails',
  );


  //SE REALIZA UNA DESUSCRIPCIÓN
    //Checkbox
  $variables['variable_mails_enviar_suscriptor_desuscripcion'] = array(
    'title' => t('Enviar mail al desuscriptor de la oferta en la desuscripción a la oferta', array(), $options),
    'type' => 'boolean',
    'default' => TRUE,
    'group' => 'variable_mails',
  );  
    // Texto para el desuscriptor
  $variables['variable_mails_offer_unsubscriber_[mail_part]'] = array(
    'type' => 'mail_text',
    'title' => t('Se realiza una duscripción', array(), $options),
    'default' => array(
      'subject' => t('Registro de desuscripción enviado por @site-name', array(), $options),
      'body' => t('@name Le envía a usted un mensaje de confirmación de baja de su suscripción a la oferta:', array(), $options),
    ),
    'description' => t('Correo enviado al desuscriptor.', array(), $options),
    'required' => TRUE,
    'group' => 'variable_mails',
  );
    //Checkbox
  $variables['variable_mails_enviar_creador_desuscripcion'] = array(
    'title' => t('Enviar mail al creador de la oferta en la desuscripción a la oferta', array(), $options),
    'type' => 'boolean',
    'default' => TRUE,
    'group' => 'variable_mails',
  );  
 $variables['variable_mails_unsubscriber_offer_owner_[mail_part]'] = array(
    'type' => 'mail_text',
    'title' => t('Se realiza una duscripción', array(), $options),
    'default' => array(
      'subject' => t('Registro de desuscripción enviado por @user-name', array(), $options),
      'body' => t('@user-name se acaba de desuscribir a una de tus ofertas con los siguientes datos:', array(), $options),
    ),
    'description' => t('Correo enviado al creador de la oferta informando de una desuscripcion.', array(), $options),
    'required' => TRUE,
    'group' => 'variable_mails',
  );

 //SE CIERRA UNA OFERTA
  //Checkbox
  $variables['variable_mails_enviar_creador_cierre'] = array(
    'title' => t('Enviar mail al creador de la oferta avisando el cierre de la misma', array(), $options),
    'type' => 'boolean',
    'default' => TRUE,
    'group' => 'variable_mails',
  );  
    // Texto para el desuscriptor
  $variables['variable_mails_closed_offer_creador_[mail_part]'] = array(
    'type' => 'mail_text',
    'title' => t('Se cierra una oferta', array(), $options),
    'default' => array(
      'subject' => t('Registro de apertura de oferta enviado por @site-name', array(), $options),
      'body' => t('@name Le comunica que una de sus ofertas se ha cerrado con éxito, los de detalles de la misma a continuación:', array(), $options),
    ),
    'description' => t('Correo enviado al creador en caso de cierre de oferta.', array(), $options),
    'required' => TRUE,
    'group' => 'variable_mails',
  );
    //Checkbox
  $variables['variable_mails_enviar_admin_cierre'] = array(
    'title' => t('Enviar mail al administrador avisando el cierre de una oferta', array(), $options),
    'type' => 'boolean',
    'default' => TRUE,
    'group' => 'variable_mails',
  );  
 $variables['variable_mails_closed_offer_admin_[mail_part]'] = array(
    'type' => 'mail_text',
    'title' => t('Se cierra una oferta', array(), $options),
    'default' => array(
      'subject' => t('Registro de cierre de oferta de @user-name', array(), $options),
      'body' => t('Se acaba de cerrar con éxito la siguiente oferta:', array(), $options),
    ),
    'description' => t('Correo enviado al administrador en caso de cierre de oferta.', array(), $options),
    'required' => TRUE,
    'group' => 'variable_mails',
  );

 //REAPERTURA DE UNA OFERTA
  //Checkbox
  $variables['variable_mails_enviar_creador_reapertura'] = array(
    'title' => t('Enviar mail al creador de la oferta avisando de la reapertura de la misma', array(), $options),
    'type' => 'boolean',
    'default' => TRUE,
    'group' => 'variable_mails',
  );  
    // Texto para el desuscriptor
  $variables['variable_mails_open_offer_creador_[mail_part]'] = array(
    'type' => 'mail_text',
    'title' => t('Se reabre una oferta', array(), $options),
    'default' => array(
      'subject' => t('Registro de apertura de oferta enviado por @site-name', array(), $options),
      'body' => t('@name Le comunica que una de sus ofertas se ha abierto por baja de un suscriptor, los de detalles de la misma a continuación:', array(), $options),
    ),
    'description' => t('Correo enviado al creador en caso de reapertura de una oferta.', array(), $options),
    'required' => TRUE,
    'group' => 'variable_mails',
  );
    //Checkbox
  $variables['variable_mails_enviar_admin_reapertura'] = array(
    'title' => t('Enviar mail al administrador avisando de la reapertura de una oferta', array(), $options),
    'type' => 'boolean',
    'default' => TRUE,
    'group' => 'variable_mails',
  );  
 $variables['variable_mails_open_offer_admin_[mail_part]'] = array(
    'type' => 'mail_text',
    'title' => t('Se reabre una oferta', array(), $options),
    'default' => array(
      'subject' => t('Registro de apertura de oferta de @user-name', array(), $options),
      'body' => t('Se acaba de abrir siguiente oferta:', array(), $options),
    ),
    'description' => t('Correo enviado al administrador en caso de reapertura de oferta.', array(), $options),
    'required' => TRUE,
    'group' => 'variable_mails',
  );
  return $variables;
}

/**
 * Implements hook_variable_group_info().
 */
function variable_mails_variable_group_info() {
  $groups['variable_mails'] = array(
    'title' => t('Mails'),
    'description' => t('Configuración de las variables de correos enviados para las ofertas de nueva creación.'),
    'access' => 'administer site configuration',
    'path' => array('admin/config/system/variable_mails'),
  );
  return $groups;
}

