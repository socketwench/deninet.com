<?php
/**
 * @file
 * deninet_topics.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function deninet_topics_taxonomy_default_vocabularies() {
  return array(
    'topics' => array(
      'name' => 'Topics',
      'machine_name' => 'topics',
      'description' => 'Category for content',
      'hierarchy' => 1,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
  );
}
