<?php
/**
 * @file
 * deninet_demo_tags.features.uuid_term.inc
 */

/**
 * Implements hook_uuid_features_default_terms().
 */
function deninet_demo_tags_uuid_features_default_terms() {
  $terms = array();

  $terms[] = array(
    'name' => 'docker from scratch',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => '0addffd5-c822-4477-b84d-129a795cc4fe',
    'vocabulary_machine_name' => 'tags',
  );
  $terms[] = array(
    'name' => 'docker',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => '8009f1ae-383b-4276-9a97-0f7b5ef73c78',
    'vocabulary_machine_name' => 'tags',
  );
  $terms[] = array(
    'name' => 'virtualization',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => '855cc694-3dc0-409d-b655-baf4c7d1084f',
    'vocabulary_machine_name' => 'tags',
  );
  $terms[] = array(
    'name' => 'devops',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => '8ef73398-5732-46e7-a04f-1f7625d4b70f',
    'vocabulary_machine_name' => 'tags',
  );
  $terms[] = array(
    'name' => 'web dev',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => 'bb2c350d-3279-41c5-9030-1e09a6d36d0d',
    'vocabulary_machine_name' => 'tags',
  );
  return $terms;
}
