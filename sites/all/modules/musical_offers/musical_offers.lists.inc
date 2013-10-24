<?php
/**
* @file
* Resultado de llamadas a páginas de administración para el módulo
* Node Expiration Date.
*/


function offers_form_lists($id,$operacion){
	global $user;	
	$output = '';
	$opt = obtiene_instrumentos();
	
	//$output .= theme('field',$lista);
	//$output .=offers_form_lists(0,'offers_list');
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

			$output .= theme('table', array('header' => $header, 'rows' => $rows));
			$output .= theme('pager');
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

			$output .= theme('table', array('header' => $header, 'rows' => $rows));
			$output .= theme('pager');
			break;
		case 'offers_list':
		
			$form= array();
			$rows = obtiene_rows_listado($id,$header);
			    // Create a jump menu
				  ctools_include('jump-menu');
				  $form = drupal_get_form('ctools_ajax_filtro');
				  $output .= '<h3><strong>'. t('Elije un instrumento para filtrar las ofertas:') .'</strong></h3>';
				  $output .= drupal_render($form);
			    
			break;
		case 'offers_list_filtro':
		$form= array();
			$rows = obtiene_rows_listado($id,$header);
			    // Create a jump menu
				  ctools_include('jump-menu');
				  $form = drupal_get_form('ctools_ajax_filtro',$id);
				  $output .= '<h3><strong>'. t('Elije un instrumento para filtrar las ofertas:') .'</strong></h3>';
				  $output .= drupal_render($form);
			    
			break;
	}

	$output .= theme('table', array('header' => $header, 'rows' => $rows));
	$output .= theme('pager');

  return $output;
}

function obtiene_rows_listado($id,$header){
	$rows = array();
	$dbOffer = new DbOffer();
	$offers = 0;
	if ($id==0) {
		$offers = $dbOffer->getOfferList($header);
	}
	else{
		$offers = $dbOffer->getOfferListWithAInstrument($id,$header);
	}
			
			$options = array();
			  if (!empty($offers)) {
			    
			    foreach ($offers as $entry) {

			    	$user_data = user_load($entry->uid);
			    	
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
													
											'#title' => (!empty($user_data->field_nombre_y_apellido['und'][0]['family']))?$user_data->field_nombre_y_apellido['und'][0]['family'].', '.$user_data->field_nombre_y_apellido['und'][0]['given']:'',
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
			   
			  }
			  else {
			    drupal_set_message(t('No records found'));
			  }

			  return $rows;
			  
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

/**
 * Helper function to provide a sample jump menu form
 */
function ctools_ajax_filtro() {
	//obtengo el valor por defecto
	 $arg2 = arg(2);
	$opts = obtiene_instrumentos();
	$list = array();
	$default_value ='';
	foreach ($opts as $key => $value) {
		if ($key!=1 && $key!=2 && $key!=3 ) {
			$url = url('listado/filtro/'.$key);
			$list[$url]= $value;
			if ($key==$arg2) {
				$default_value = $url;
			}
		}
		
	}
  $form_state = array();
  $form = ctools_jump_menu(array(), $form_state, $list, array('default_value'=>$default_value));
  return $form;
}