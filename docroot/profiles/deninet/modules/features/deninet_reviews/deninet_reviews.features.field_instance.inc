<?php
/**
 * @file
 * deninet_reviews.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function deninet_reviews_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'node-review-field_add_sections'.
  $field_instances['node-review-field_add_sections'] = array(
    'bundle' => 'review',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'paragraphs',
        'settings' => array(
          'view_mode' => 'full',
        ),
        'type' => 'paragraphs_view',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_add_sections',
    'label' => 'Add Sections',
    'required' => 1,
    'settings' => array(
      'add_mode' => 'select',
      'allowed_bundles' => array(
        'audio_playlist' => -1,
        'image_gallery' => -1,
        'simple_text' => -1,
      ),
      'bundle_weights' => array(
        'audio_playlist' => 2,
        'image_gallery' => 3,
        'simple_text' => 4,
      ),
      'default_edit_mode' => 'open',
      'title' => 'Paragraph',
      'title_multiple' => 'Paragraphs',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'paragraphs',
      'settings' => array(),
      'type' => 'paragraphs_embed',
      'weight' => 4,
    ),
  );

  // Exported field_instance: 'node-review-field_disliked_moments'.
  $field_instances['node-review-field_disliked_moments'] = array(
    'bundle' => 'review',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'A moment you did not like from what you\'re reviewing. If you have more than one, add one for each moment.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 3,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_disliked_moments',
    'label' => 'Disliked moments',
    'required' => 0,
    'settings' => array(
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 3,
      ),
      'type' => 'text_textarea',
      'weight' => 6,
    ),
  );

  // Exported field_instance: 'node-review-field_favorite_moments'.
  $field_instances['node-review-field_favorite_moments'] = array(
    'bundle' => 'review',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'A favorite moment or aspect of what you\'re reviewing. If you have more than one, add one for each.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 2,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_favorite_moments',
    'label' => 'Favorite moments',
    'required' => 0,
    'settings' => array(
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 3,
      ),
      'type' => 'text_textarea',
      'weight' => 5,
    ),
  );

  // Exported field_instance: 'node-review-field_tagline'.
  $field_instances['node-review-field_tagline'] = array(
    'bundle' => 'review',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'A quick summary of your review.',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 1,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_tagline',
    'label' => 'Tagline',
    'required' => 1,
    'settings' => array(
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 3,
      ),
      'type' => 'text_textarea',
      'weight' => 1,
    ),
  );

  // Exported field_instance: 'node-review-field_topic'.
  $field_instances['node-review-field_topic'] = array(
    'bundle' => 'review',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'taxonomy',
        'settings' => array(),
        'type' => 'taxonomy_term_reference_link',
        'weight' => 4,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_topic',
    'label' => 'Topic',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_select',
      'weight' => 2,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('A favorite moment or aspect of what you\'re reviewing. If you have more than one, add one for each.');
  t('A moment you did not like from what you\'re reviewing. If you have more than one, add one for each moment.');
  t('A quick summary of your review.');
  t('Add Sections');
  t('Disliked moments');
  t('Favorite moments');
  t('Tagline');
  t('Topic');

  return $field_instances;
}
