<?php

/**
 * @file
 * An example of how to use the new #states Form API element, allowing
 * dynamic form behavior with very simple setup.
 */

/**
 * This form shows off the #states system by dynamically showing parts of the
 * form based on the state of other parts.
 *
 * @ingroup form_example
 *
 * The basic idea is that you add a #states property to the element which is
 * to be changed based on some action elsewhere on the form. The #states
 * property lists a change which is to be made, and under what conditions
 * that change should be made.
 *
 * For example, in the 'tests_taken' form element below we have:
 * @code
 * '#states' => array(
 *   'visible' => array(
 *     ':input[name="student_type"]' => array('value' => 'high_school'),
 *   ),
 * ),
 * @endcode
 * Meaning that the element is to be made visible when the condition is met.
 * The condition is a combination of a jQuery selector (which selects the
 * element we want to test) and a condition for that element. In this case,
 * the condition is whether the return value of the 'student_type' element is
 * 'high_school'. If it is, this element will be visible.
 *
 * So the syntax is:
 * @code
 * '#states' => array(
 *   'action_to_take_on_this_form_element' => array(
 *     'jquery_selector_for_another_element' => array('condition_type' => value),
 *   ),
 * ),
 * @endcode
 *
 * If you need an action to take place only when two different conditions are
 * true, then you add both of those conditions to the action. See the
 * 'country_writein' element below for an example.
 *
 * Note that the easiest way to select a textfield, checkbox, or select is with
 * the @link http://api.jquery.com/input-selector/ ':input' jquery shortcut @endlink,
 * which selects any any of those.
 *
 * There are examples below of changing or hiding an element when a checkbox
 * is checked, when a textarea is filled, when a select has a given value.
 *
 * See drupal_process_states() for full documentation.
 *
 * See also @link http://api.drupal.org/api/drupal/developer--topics--forms_api_reference.html/7#states Form API Reference @endlink
 */
function forms_forcontu_states_form($form, &$form_state) {

	 $form['performers']['school_country'] = array(
    '#type' => 'select',
    '#options' => drupal_map_assoc(array(t('UK'), t('Other'))),
    '#title' => t('In what country is your college or university located?'),
 	 );
  	$form['performers']['country_writein'] = array(
    '#type' => 'textfield',
    '#size' => 20,
    '#title' => t('Please enter the name of the country where your college or university is located.'),

    // Only show this field if school_country is set to 'Other'.
    '#states' => array(
      'visible' => array(  // Action to take: Make visible.
        ':input[name="school_country"]' => array('value' => t('Other')),
      ),
    ),
  );
}