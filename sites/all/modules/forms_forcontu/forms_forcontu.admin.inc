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

function offers_form_views($form,&$form_state,$operacion){
	global $user;	
	$id = $form_state['build_info']['args'][0];
		
	
	$form = array();
	$options = obtiene_instrumentos();
	$dbOferta = new DbOffer();
	$oferta = $dbOferta->get($id);
	//Instrumentos seleccionados por el usuario actual
	$instrumentos_usuario = db_select('pym_instrumentos_ofertas', 'io')
			//->fields('io', array('uid'))
			->condition('nid_oferta', $id,'=')
			->condition('uid', $user->uid,'=');

	$instrumentos_usuario->addExpression('COUNT(uid)', 'uid_count');
	
	$ii = $instrumentos_usuario->execute()->fetchObject();
	//Se activa con la primera aparición del nombre en la lista de suscriptos
	if($ii->uid_count>0) {
		$booleanSuscripcion = TRUE;
		drupal_set_message('You are already subscribed to this offer. You havent got permission to select another one');
	}
	else
	{
		$booleanSuscripcion = FALSE;
	}
	switch ($operacion) {
		case 'edit':
		
			$form['actions'] = array('#type' => 'actions');
			$form['actions']['submit'] = array(
				'#type' => 'submit',
				'#value' => t('Save'),
			//'#attributes' => array('onclick' => 'if(!confirm("Really want to subscribe?")){return false;}')
			);
			break;
		case 'view':
			
			if($booleanSuscripcion ){
		 	//botones
			$form['actions'] = array('#type' => 'actions');
			$form['actions']['submit'] = array(
				'#type' => 'submit',
				'#value' => t('Unsubscribe'),
				//'#attributes' => array('onclick' => 'if(!confirm("Really want to subscribe?")){return false;}')
			);

			}
			else{
				//botones
				$form['actions'] = array('#type' => 'actions');
				$form['actions']['submit'] = array(
					'#type' => 'submit',
					'#value' => t('Subscribe'),
					//'#attributes' => array('onclick' => 'if(!confirm("Really want to subscribe?")){return false;}')
				);
			}
			break;
		default:
			# code...
			break;
	}
	


	$form['nid_oferta'] = array(
		'#type' => 'hidden',
		'#title' => t('Oferta'),
		'#value' => $id,
	);

	

	$form['personal_data'] = array(
		'#type' => 'fieldset',
		'#title' => t('Datos de la oferta. Creado:').' <strong> '.date('d-M-Y', $oferta->getFechaCreacion()).'</strong>',
		'#collapsible' => TRUE,
		'#collapsed' => FALSE,
	);
	$form['personal_data']['mail'] = array(
		'#type' => 'hidden',
		'#default_value' => $oferta->getUser_mail(),
	);
	/*$form['personal_data']['creador_oferta'] = array(
		'#type' => 'textfield',
		'#title' => t('Creador de la oferta'),
		'#default_value' => $oferta->getUser_name(),
		'#required' => TRUE,
	);*/
	$form['personal_data']['a_oferta'] = array(
		'#type' => 'item',
		'#title' => t('Autor de la oferta'),
		'#markup' => t('!url', array('!url' => l(t($oferta->getUser_name()), "user/".$oferta->getUid()))),
	);	
	$form['personal_data']['obra_musical'] = array(
		'#type' => ($operacion=='view')?'item':'textfield',
		'#title' => t('Music piece'),
		($operacion=='view')?'#markup':'#default_value' => $oferta->getObra_musical(),
		'#required' => TRUE,
	);
	$form['personal_data']['autor_obra'] = array(
		'#type' => ($operacion=='view')?'item':'textfield',
		'#title' => t('Autor de la Obra'),
		($operacion=='view')?'#markup':'#default_value' => $oferta->getAutor_obra(),
		'#required' => TRUE,
	);

	if($operacion=='view'){
		$dbInstrument = new DbInstrument();
		$inst = $dbInstrument->get($oferta->getInstrumento_autor());
		$form['personal_data']['a_instrumet'] = array(
		'#type' => 'item',
		'#title' => t('Instrument to play by the author:'),
		'#markup' => $inst->getName_instrument(),
		
	);
	}else{

		$form['personal_data']['autor_instrumet'] = array(
				'#type' => 'select',
				'#title' => t('Instrument to play by the author'),
				'#required' => TRUE,
				'#options' => $options,
				'#value' => $oferta->getInstrumento_autor(),
		        '#empty' => t('No content available.'),
			);
	}
	

	if($operacion=='view'){
		
		$form['personal_data']['Salon'] = array(
				'#type' => 'item',
				'#title' => t('Se necesita Salon'),
				'#markup' => ($oferta->getSalon()==0)?'No':'Si',
			);
			$form['personal_data']['Piano'] = array(
				'#type' => 'item',
				'#title' => t('Se necesita Piano'),
				'#markup' => ($oferta->getPiano()==0)?'No':'Si',
			);
	}else
	{
		$form['personal_data']['Salom'] = array(
			'#type' => 'checkbox',
			'#title' => t('Se necesita Salon'),
			'#default_value' => ($oferta->getSalon()==0)?0:1,
		);
		$form['personal_data']['Piano'] = array(
			'#type' => 'checkbox',
			'#title' => t('Se necesita Piano'),
			'#default_value' => ($oferta->getPiano()==0)?0:1,
		    '#states' => array(
		      'visible' => array(  // Action to take: Make visible.
		        ':input[name="Salom"]' => array('checked' => TRUE),
		      ),
	    	),
		);
		}
	


	
	$form['personal_data']['Ciudad'] = array(
		'#type' => ($operacion=='view')?'item':'textfield',
		'#title' => t('City to play'),
		($operacion=='view')?'#markup':'#default_value' => $oferta->getCiudad(),
		'#required' => TRUE,
	);
	$form['personal_data']['Disponibilidad'] = array(
		'#type' => ($operacion=='view')?'item':'textfield',
		'#title'=> t('Availability'),
		($operacion=='view')?'#markup':'#default_value' => $oferta->getDisponibilidad(),
		//'#collapsed' => FALSE,
	);

	$form['instruments']= array(
		'#type' => 'fieldset',
		'#title'=> t('Instruments'),
		'#collapsible' => TRUE,
		'#collapsed' => FALSE,
		'#description' => t('Select the instrument wich you want to suscribe to.'),
	);

	
	$header = array(
		'Instrumento' => array('data' => t('Instrumento'), 'field' => 'i.name_instrument'),
		'Suscriptor' => array('data' => t('Suscriptor'), 'field' => 'u.name'),
		'Activo' => array('data' => t('Estado'), 'field' => 'io.position'),
	
	);
	$instrumentos = db_select('pym_instrumentos_ofertas', 'io')
			->fields('io', array('nid_oferta', 'nid_instrument', 'uid','position'))
			->condition('nid_oferta', $id,'=');
			//->condition('activo', 1,'=');
	$instrumentos->addField('u', 'name', 'name');
	$instrumentos->addField('i', 'name_instrument', 'name_instrument');
	$instrumentos->leftJoin('users', 'u', 'io.uid = u.uid ');
	$instrumentos->leftJoin('instruments', 'i', 'io.nid_instrument = i.nid_instrument ');
	//defino una línea de instrumento 
  	$entries = $instrumentos->execute()->fetchAll();

	

	$options = array();
	$optout = array();
	
	    foreach ($entries as $entry) {
	      $key = $entry->nid_instrument.'-'.$entry->nid_oferta.$entry->position;
        
	      if(evaluaCondiciones($entry,$user,$oferta) || $booleanSuscripcion)$optout[$key] = TRUE;
	      $options[$key] = array(

						'Instrumento' => check_plain($entry->name_instrument),
						'Suscriptor' => array(
									'data' => array(
									'#type' => 'link',
									'#title' => $entry->name,
									'#href' => 'user/' . $entry->uid,
									),
						),
						'Activo' => (empty($entry->name))?'Si':'No',
						);
	    }
	 

	$form['instruments']['instruments'] = array(
		'#type' => 'tableselect',
		'#header' => $header,
		'#options' => $options,
		'#empty' => t('No tiene contenido.'),
		'#multiple' => FALSE,
		//'#required' => TRUE,
	);

	foreach( $optout as $key => $value )
	{
	  $form['instruments']['instruments'][$key]['#disabled'] = true;
	}
 	
	

	
	return $form;
}

function obtiene_instrumentos(){
	$query = db_select('instruments', 'n');
	// Obtiene los datos de la base de datos (tabla node).
	$instruments = $query->
		fields('n',array('nid_instrument','name_instrument'))
		->condition('general_list', 1,'=')->execute();
	$options = array();
	foreach ($instruments as $result) {
    	$options[$result->nid_instrument] = $result->name_instrument;
	}
	return $options;
}