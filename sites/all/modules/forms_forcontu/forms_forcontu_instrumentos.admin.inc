<?php
/**
* @file
* Resultado de llamadas a páginas de administración para el módulo
* Node Expiration Date.
*/
/**
* Constructor del formulario para configurar el módulo.
*
*/
function instruments_form_admin_settings() {
	
	$instrumentos = db_select('pym_instrumentos', 'i')
			->fields('i', array( 'nid_instrument', 'name_instrument','description_instrument'))
			->execute();

	/**
	* Con node_type_get_types() se obtiene la información de todos los tipos
	* de contenido, cada uno como un objeto, por lo que hay que seleccionar
	* sólo los nombres de los tipo de contenido para mostrarlos en las opciones.
	*/
	$content_types_list = node_type_get_types();
	foreach ($instrumentos as $key) {
		//$key = entry
		$list[$key->nid_instrument] = $key->name_instrument;
	}

	$form['offers_form_types'] = array(
		'#type' => 'checkboxes',
		'#title' => t('Add an instrument to the list'),
		'#options' => $list,
		//'#theme' => 'table',
		'#default_value'=> variable_get('offers_form', array('page')),
		'#description' => t('The selected content types will have an
		expiration date.'),
	);

/*$form['people'] = array(
  '#prefix' => '<div id="people">',
  '#suffix' => '</div>',
  '#tree' => TRUE,
  '#theme' => 'table',
  '#header' => array(t('instrumento')),
  '#rows' => $list,
  );*/
	$form['myfield'] = array(
        '#title' => 'New one',
        '#description' => 'This is a basic text input field',
        '#type' => 'textfield',
        '#default_value' => variable_get('myfield', array('page')),
    );
    $form['actions'] = array('#type' => 'actions');
		$form['actions']['submit'] = array(
			'#type' => 'submit',
			'#value' => t('Update'),
			//'#attributes' => array('onclick' => 'if(!confirm("Really want to subscribe?")){return false;}')
		);
	return $form;
}

/**
* Función de validación.
*/
function offers_form_admin_settings_validate($form, &$form_state){
	 drupal_set_message ("<strong>Hubo un problema en el registro de su oferta, por favor inténtelo más tarde.</br></strong> ");
	return false;
}
function offers_form_admin_settings_submit($form, &$form_state){
	 drupal_set_message ("<strong>Hubo un problema en el registro de su oferta, por favor inténtelo más tarde.</br></strong> ");
	 drupal_goto("");
}