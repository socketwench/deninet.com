<?php
/**
 * @file
 * deninet_collections.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function deninet_collections_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_collection_items'.
  $field_bases['field_collection_items'] = array(
    'active' => 1,
    'cardinality' => -1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_collection_items',
    'indexes' => array(
      'target_id' => array(
        0 => 'target_id',
      ),
    ),
    'locked' => 0,
    'module' => 'entityreference',
    'settings' => array(
      'handler' => 'base',
      'handler_settings' => array(
        'behaviors' => array(
          'views-select-list' => array(
            'status' => 0,
          ),
        ),
        'sort' => array(
          'type' => 'none',
        ),
        'target_bundles' => array(
          'art' => 'art',
          'audio' => 'audio',
          'blog' => 'blog',
          'book' => 'book',
          'link' => 'link',
          'picture' => 'picture',
        ),
      ),
      'target_type' => 'node',
    ),
    'translatable' => 0,
    'type' => 'entityreference',
  );

  return $field_bases;
}
