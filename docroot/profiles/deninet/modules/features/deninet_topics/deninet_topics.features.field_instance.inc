<?php
/**
 * @file
 * deninet_topics.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function deninet_topics_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'taxonomy_term-topics-field_featured'.
  $field_instances['taxonomy_term-topics-field_featured'] = array(
    'bundle' => 'topics',
    'default_value' => array(
      0 => array(
        'value' => 0,
      ),
    ),
    'deleted' => 0,
    'description' => 'Featured topics will appear in the Featured Topics pages and blocks.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 1,
      ),
    ),
    'entity_type' => 'taxonomy_term',
    'field_name' => 'field_featured',
    'label' => 'featured',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'display_label' => 0,
      ),
      'type' => 'options_onoff',
      'weight' => 1,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Featured topics will appear in the Featured Topics pages and blocks.');
  t('featured');

  return $field_instances;
}
