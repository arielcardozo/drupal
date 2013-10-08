<?php
/**
* @file
* Resultado de llamadas a páginas de administración para el módulo
* Node Expiration Date.
*/


function offers_form_lists($id,$operacion){
	global $user;	
	$output = '';
	$header = obtiene_cabecera($operacion);
	$rows = array();

	switch ($operacion) {
		case 'offers_made':
			$query = db_select('pym_ofertas', 'pym');
			//$query->range(0, 10);
			// Obtiene los datos de la base de datos (tabla node).
			$query->fields('pym',array('nid_oferta','uid','fecha_creacion','autor_obra','obra_musical','ciudad','activo'))
						->condition('u.uid', $id,'=');
			$query->join('users', 'u', 'u.uid = pym.uid');
			      

			$query = $query->extend('PagerDefault')->limit(20); // line1
			$query = $query->extend('TableSort');
			$offers = $query->orderByHeader($header)->execute()->fetchAll();
			$rows = obtiene_rows($id,$offers,$operacion);
			break;
		case 'subscriptions_made':
			$suscripciones = db_select('pym_instrumentos_ofertas', 'pym_io');
			$suscripciones->fields('pym_io',array('nid_oferta'))
							->condition('pym_io.uid', $id,'=');
		    $suscripciones->addField('pym', 'nid_oferta');
		    $suscripciones->addField('pym', 'uid');
		    $suscripciones->addField('pym', 'fecha_creacion');
		    $suscripciones->addField('pym', 'autor_obra');
		    $suscripciones->addField('pym', 'obra_musical');
		    $suscripciones->addField('pym', 'ciudad');
		    $suscripciones->addField('pym', 'activo');
			$suscripciones->leftJoin('pym_ofertas', 'pym', 'pym_io.nid_oferta = pym.nid_oferta');


			$suscripciones = $suscripciones->extend('PagerDefault')->limit(20); // line1
			$suscripciones = $suscripciones->extend('TableSort');
			$offers = $suscripciones->orderByHeader($header)->execute()->fetchAll();
			$rows = obtiene_rows($id,$offers,$operacion);
			break;
		default:
			$dbOffer = new DbOffer();
			$offers = $dbOffer->getOfferList($header);
			$options = array();
			  if (!empty($offers)) {
			    $rows = array();
			    foreach ($offers as $entry) {

			    	$user_data = user_load($entry->uid);
			    	//dpm($user_data,'user_data');
			 		//dpm($user_data->field_nombre_y_apellido['und'][0]['given'],'given');
			    	$row = array(
						'created' => date('d-M-Y', $entry->fecha_creacion),
						'Music piece' => array(
										'data' => array(
													'#type' => 'link',
													'#title' => $entry->obra_musical,
													
													'#href' => 'ofertas/'.$entry->nid_oferta.'/user/'.$entry->uid.'/detalle/view' ,
													'#options' => $options,
													),
												),
						
						'Author Oferta' => array(
										'data' => array(
													'#type' => 'link',
													//'#title' => $entry->name,
													'#title' => $user_data->field_nombre_y_apellido['und'][0]['family'].', '.$user_data->field_nombre_y_apellido['und'][0]['given'],
													'#href' => 'user/' . $entry->uid,
													'#options' => $options,
													),
												),

						'Ciudad' => $entry->ciudad,	
						'Estado' => (empty($entry->activo))?t('Closed'):t('Open'),

					);
			      $rows[] = $row;
			    }
			    // Make a table for them.
			    //$header = array(t('created'), t('Music piece'), t('Offer Author'),t('Estado'));
			    
			  }
			  else {
			    drupal_set_message(t('No records found'));
			  }
			break;
	}
	$output .= theme('table', array('header' => $header, 'rows' => $rows));
	$output .= theme('pager');
  return $output;
}

function obtiene_cabecera($tipo_listado){
	$header = '';
	switch ($tipo_listado) {
		case 'offers_list':
			$header = array(
			'created' => array('data' => t('Created'), 'field' => 'fecha_creacion','sort' => 'desc'),
			'Music piece' => array('data' => t('Music piece'), 'field' => 'obra_musical'),
			'Author Oferta' => array('data' => t('Offer\'s Author'), 'field' => 'name','sort' => 'asc'),
			'Ciudad' => array('data' => t('City'), 'field' => 'ciudad','sort' => 'asc'),

			'Activo' => array('data' => t('State'), 'field' => 'activo','sort' => 'asc'),
			);
			break;
		default:
			$header = array(
			'created' => array('data' => t('Created'), 'field' => 'fecha_creacion','sort' => 'desc'),
			'Music piece' => array('data' => t('Music piece'), 'field' => 'obra_musical'),
			'Author Obra' => array('data' => t('Author'), 'field' => 'name','sort' => 'asc'),
			'Ciudad' => array('data' => t('City'), 'field' => 'ciudad','sort' => 'asc'),
			'Activo' => array('data' => t('State'), 'field' => 'activo','sort' => 'asc'),
			);
			break;

	}
	
	return $header;
}

function obtiene_rows($id,$offers,$operacion){
	
	$rows = array();
	$options = array();
	if (!empty($offers)) {
	    
	    foreach ($offers as $entry) {
	      // Sanitize the data before handing it off to the theme layer.
	    	$row = array(
				'created' => date('d-M-Y', $entry->fecha_creacion),
				'Music piece' => array(
								'data' => array(
											'#type' => 'link',
											'#title' => $entry->obra_musical,
											'#href' => 'ofertas/'.$entry->nid_oferta.'/user/'.$entry->uid.'/detalle/view' ,
											'#options' => $options,
											),
										),
				
				
				'Author Obra' => $entry->autor_obra,
				'Ciudad' => $entry->ciudad,
				//'Estado' => $entry->activo,
				'Estado' => (empty($entry->activo))?t('Closed'):t('Open'),

			);
	      $rows[] = $row;
	    }
	}
    return $rows;
}