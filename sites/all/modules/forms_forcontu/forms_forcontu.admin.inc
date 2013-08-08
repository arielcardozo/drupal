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
function offers_form_admin_settings() {
	/**
	* Con node_type_get_types() se obtiene la información de todos los tipos
	* de contenido, cada uno como un objeto, por lo que hay que seleccionar
	* sólo los nombres de los tipo de contenido para mostrarlos en las opciones.
	*/
	$content_types_list = node_type_get_types();
	foreach ($content_types_list as $key => $type) {
		$list[$key] = $type->name;
	}
	$form['offers_form_types'] = array(
		'#type' => 'checkboxes',
		'#title' => t('Add an expiration date to these content types'),
		'#options' => $list,
		'#default_value'=> variable_get('offers_form_types', array('page')),
		'#description' => t('The selected content types will have an
		expiration date.'),
	);

	$form['myfield'] = array(
        '#title' => 'My Field',
        '#description' => 'This is a basic text input field',
        '#type' => 'textfield',
        '#default_value' => variable_get('myfield', array('page')),
    );
return system_settings_form($form);
}

/**
* Función de validación.
*/
function offers_form_admin_settings_validate($form,
&$form_state){
//Validación de campos del formulario
}