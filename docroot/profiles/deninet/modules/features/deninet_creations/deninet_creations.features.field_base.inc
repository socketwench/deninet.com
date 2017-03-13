<?php
/**
 * @file
 * deninet_creations.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function deninet_creations_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_add_sections'.
  $field_bases['field_add_sections'] = array(
    'active' => 1,
    'cardinality' => -1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_add_sections',
    'indexes' => array(),
    'locked' => 0,
    'module' => 'paragraphs',
    'settings' => array(),
    'translatable' => 0,
    'type' => 'paragraphs',
  );

  return $field_bases;
}
