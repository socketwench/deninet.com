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
    'description' => '',
    'format' => 'filtered_html',
    'weight' => 0,
    'uuid' => '51e9afd5-0b71-46fb-8471-0aa7bad81c10',
    'vocabulary_machine_name' => 'topics',
    'field_featured' => array(
      'und' => array(
        0 => array(
          'value' => 1,
        ),
      ),
    ),
    'path' => array(
      'pathauto' => 1,
    ),
  );
  $terms[] = array(
    'name' => 'Electronics',
    'description' => '',
    'format' => 'filtered_html',
    'weight' => 0,
    'uuid' => '659b0b7a-5321-45c1-9a17-0c27f9309c1d',
    'vocabulary_machine_name' => 'topics',
    'field_featured' => array(
      'und' => array(
        0 => array(
          'value' => 0,
        ),
      ),
    ),
    'path' => array(
      'pathauto' => 1,
    ),
  );
  $terms[] = array(
    'name' => 'Linux',
    'description' => '',
    'format' => 'filtered_html',
    'weight' => 0,
    'uuid' => '6d3c68bd-9759-4ea7-9877-7c2213bdd321',
    'vocabulary_machine_name' => 'topics',
    'field_featured' => array(
      'und' => array(
        0 => array(
          'value' => 0,
        ),
      ),
    ),
    'path' => array(
      'pathauto' => 1,
    ),
  );
  $terms[] = array(
    'name' => 'Networking',
    'description' => '',
    'format' => 'filtered_html',
    'weight' => 0,
    'uuid' => 'bf722a4b-5729-404f-9a7f-e8a20b0d4610',
    'vocabulary_machine_name' => 'topics',
    'field_featured' => array(
      'und' => array(
        0 => array(
          'value' => 0,
        ),
      ),
    ),
    'path' => array(
      'pathauto' => 1,
    ),
  );
  $terms[] = array(
    'name' => 'Drupal',
    'description' => '',
    'format' => 'filtered_html',
    'weight' => 0,
    'uuid' => 'e090cbee-0566-48d5-b916-23082cd55c98',
    'vocabulary_machine_name' => 'topics',
    'field_featured' => array(
      'und' => array(
        0 => array(
          'value' => 1,
        ),
      ),
    ),
    'path' => array(
      'pathauto' => 1,
    ),
  );
  return $terms;
}
