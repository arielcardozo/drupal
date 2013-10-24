<?php
/**
* @file
* Resultado de llamadas a páginas de administración para el módulo
* Node Expiration Date.
*/


function offers_form_views(&$form_state,$operacion){
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
	//dpm($form_state);
	//Se activa con la primera aparición del nombre en la lista de suscriptos
	if($ii->uid_count>0) {
		$booleanSuscripcion = TRUE;
		if(!isset($form_state['input']['op'])){
			drupal_set_message(t('You are already subscribed to this offer. You havent got permission to select another one'));
		}

		
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
			
			if($booleanSuscripcion){
				$form['booleanSuscripcion'] = array(
					'#type' => 'hidden',
					'#value' => 'TRUE',
					//'#attributes' => array('onclick' => 'if(!confirm("Really want to subscribe?")){return false;}')
				);
			 	//botones
				$form['actions'] = array('#type' => 'actions');
				$form['actions']['submit'] = array(
					'#type' => 'submit',
					'#value' => t('Unsubscribe'),
					//'#attributes' => array('onclick' => 'if(!confirm("Really want to subscribe?")){return false;}')
				);

			}
			else{
				if($oferta->getActivo()==1){
					//botones
					$form['actions'] = array('#type' => 'actions');
					$form['actions']['submit'] = array(
						'#type' => 'submit',
						'#value' => t('Subscribe'),
						//'#attributes' => array('onclick' => 'if(!confirm("Really want to subscribe?")){return false;}')
					);
				}
				
			}
			break;

	}
	

	$form['nid_oferta'] = array(
		'#type' => 'hidden',
		'#title' => t('Offer'),
		'#value' => $id,
	);

	

	$form['personal_data'] = array(
		'#type' => 'fieldset',
		'#title' => t('Offer details. Created:').' <strong> '.date('d-M-Y', $oferta->getFechaCreacion()).'</strong>',
		'#collapsible' => TRUE,
		'#collapsed' => FALSE,
	);
	$form['personal_data']['mail'] = array(
		'#type' => 'hidden',
		'#default_value' => $oferta->getUser_mail(),
	);

	$user_full_name = get_full_name($oferta->getUid());
	$form['personal_data']['a_oferta'] = array(
		'#type' => 'item',
		'#title' => t('Offer\'s author'),
		'#markup' => t('!url', array('!url' => l($user_full_name, "user/".$oferta->getUid()))),
	);	
	
	$form['personal_data']['obra_musical'] = array(
		'#type' => ($operacion=='view')?'item':'textfield',
		'#title' => t('Music piece'),
		($operacion=='view')?'#markup':'#default_value' => $oferta->getObra_musical(),
		'#required' => ($operacion=='view')?'':TRUE,
	);

	$form['personal_data']['autor_obra'] = array(
		'#type' => ($operacion=='view')?'item':'textfield',
		'#title' => t('Author'),
		($operacion=='view')?'#markup':'#default_value' => $oferta->getAutor_obra(),
		'#required' => ($operacion=='view')?'':TRUE,
	);
	

	if($operacion=='view'){
		$dbInstrument = new DbInstrument();

		$inst = $dbInstrument->get($oferta->getInstrumento_autor());
		$form['personal_data']['a_instrumet'] = array(
		'#type' => 'item',
		'#title' => t('Instrument to play by the author:'),
		'#markup' => $inst->getName_instrument(),
		
		);
		$form['ciudad'] = array(
		'#type' => 'hidden',
		'#default_value' => $oferta->getCiudad(),
		);
		$form['autor_obra'] = array(
				'#type' => 'hidden',
				'#default_value' => $oferta->getAutor_obra(),
		);
		$form['obra_musical'] = array(
			'#type' => 'hidden',
			'#default_value' => $oferta->getObra_musical(),
		);	
		$form['autor_oferta'] = array(
		'#type' => 'hidden',
		'#default_value' => $user_full_name,
		);
	}else{
	
		$form['personal_data']['autor_instrumet'] = array(
				'#type' => 'select',
				'#title' => t('Instrument to play by the author:'),
				'#required' => ($operacion=='view')?'':TRUE,
				'#options' => $options,
				'#value' => $oferta->getInstrumento_autor(),
		        '#empty' => t('No content available.'),
			);
	}
	

	if($operacion=='view'){
		
		$form['personal_data']['Salon'] = array(
				'#type' => 'item',
				'#title' => t('It takes Salon'),
				'#markup' => ($oferta->getSalon()==0)?t('No'):t('Yes'),
			);
			$form['personal_data']['Piano'] = array(
				'#type' => 'item',
				'#title' => t('Piano needed'),
				'#markup' => ($oferta->getPiano()==0)?t('No'):t('Yes'),
			);
	}else
	{
		$form['personal_data']['Salom'] = array(
			'#type' => 'checkbox',
			'#title' => t('It takes Salon'),
			'#default_value' => ($oferta->getSalon()==0)?0:1,
		);
		$form['personal_data']['Piano'] = array(
			'#type' => 'checkbox',
			'#title' => t('Piano needed'),
			'#default_value' => ($oferta->getPiano()==0)?0:1,
		    '#states' => array(
		      'visible' => array(  // Action to take: Make visible.
		        ':input[name="Salom"]' => array('checked' => TRUE),
		      ),
	    	),
		);
		}
	


	$form['personal_data']['ciudad'] = array(
		'#type' => ($operacion=='view')?'item':'textfield',
		'#title' => t('City to play'),
		($operacion=='view')?'#markup':'#default_value' => $oferta->getCiudad(),
		'#required' => ($operacion=='view')?'':TRUE,
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
		'Instrumento' => array('data' => t('Instrument'), 'field' => 'i.name_instrument'),
		'Suscriptor' => array('data' => t('Subscriber'), 'field' => 'u.name', 'sort'=>'asc'),
		'Activo' => array('data' => t('State'), 'field' => 'io.position'),
	
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
	$instrumentos = $instrumentos->extend('PagerDefault')->limit(20); // line1
    $instrumentos = $instrumentos->extend('TableSort');
  	$entries = $instrumentos->orderByHeader($header)->execute()->fetchAll();

	

	$options = array();
	$optout = array();
	
	    foreach ($entries as $entry) {
	      $key = $entry->nid_instrument.'-'.$entry->nid_oferta.$entry->position;
          $user_instrument = get_full_name($entry->uid);
	      if(evaluaCondiciones($entry,$user,$oferta) || $booleanSuscripcion)$optout[$key] = TRUE;
	      $options[$key] = array(

						'Instrumento' => check_plain($entry->name_instrument),
						'Suscriptor' => array(
									'data' => array(
									'#type' => 'link',
									'#title' =>(!empty($user_instrument))? $user_instrument:'',
									//'#title' => $entry->name,
									'#href' => 'user/' . $entry->uid,
									),
						),
						'Activo' => (empty($entry->name))?t('Open'):t('Closed'),
						);
	    }
	 /*
$form['review_overall_rating'] = array(
    '#type' => 'fivestar',
    '#title' => t('Ha estudiado la letra?'),
    '#required' => TRUE,
    '#stars' => 5,
    '#weight' => -45,
    '#description' => t('Click on the stars to set your rating.'),
  );*/
	$form['instruments']['instruments'] = array(
		'#type' => 'tableselect',
		'#header' => $header,
		'#options' => $options,
		'#empty' => t('No content.'),
		'#multiple' => FALSE,
		//'#required' => TRUE,
	);

	foreach( $optout as $key => $value )
	{
	  $form['instruments']['instruments'][$key]['#disabled'] = true;
	}
 	
 /*$path = drupal_get_path('module', 'fivestar');      
  drupal_add_js($path . '/js/fivestar.js');
  drupal_add_css($path . '/css/fivestar.css');

  $rating = votingapi_select_single_result_value(array(
        'entity_id' => YOURENTITY_ID,
        'entity_type' => 'YOURENTITY_TYPE',
        'tag' => 'vote',
        'function' => 'average',
   ));
   $form['votes'] = array(
      '#markup' =>  theme('fivestar_static', array('rating' => $rating, 'stars' => 5, 'tag' => 'vote')),
   );*/

/*	$user_data = user_load($oferta->getUid());
	//dpm($user_data->field_es_puntual['und'][0]['rating'],'rating');
	dpm($user_data,'user_data');
	 $values = array('user' => $user->uid, 'average'=>$user_data->field_es_puntual['und'][0]['rating'], 'count' => 100);

   $settings = array(
    'content_type' => 'user',
    'content_id' => $user_data->uid,
    'stars' => 5,
    'microdata' =>array(),
    'autosubmit' => TRUE,
    'field_name' => 'field_es_puntual',
    'langcode'=>'und',
    'entity' => $user_data,
    'labes_enable'=> FALSE,
    'labels'=>array(),
    'title'=>TRUE,
    'allow_clear' => 0,
    'text' => 'average', // options are none, average, smart, user, and dual
    'tag' => 'vote',
    'style' => 'average', // options are average, dual, smart, user
    'widget' => array( 'name' => 'oxygen', 'css' => drupal_get_path('module', 'fivestar') . '/widgets/oxygen/oxygen.css' ),
  );

//print render(drupal_get_form('fivestar_custom_widget', $profileView->field_profile_rating['und'][0], $settings));

   $form['custom_five_star'] = drupal_get_form('fivestar_custom_widget', $user_data->field_es_puntual['und'][0]['rating'], $settings);
*/
   
	return $form;
}

