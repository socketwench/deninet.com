<?php
/**
 * @file
 * deninet_demo_topics.features.uuid_term.inc
 */

/**
 * Implements hook_uuid_features_default_terms().
 */
function deninet_demo_topics_uuid_features_default_terms() {
  $terms = array();

  $terms[] = array(
    'name' => 'Docker',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => '51e9afd5-0b71-46fb-8471-0aa7bad81c10',
    'vocabulary_machine_name' => 'topics',
  );
  return $terms;
}
