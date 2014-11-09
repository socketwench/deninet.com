<?php
/**
 * @file
 * deninet_picture.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function deninet_picture_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'node-picture-body'
  $field_instances['node-picture-body'] = array(
    'bundle' => 'picture',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 1,
      ),
      'teaser' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(
          'trim_length' => 600,
        ),
        'type' => 'text_summary_or_trimmed',
        'weight' => 1,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'body',
    'label' => 'Body',
    'required' => FALSE,
    'settings' => array(
      'display_summary' => TRUE,
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'module' => 'text',
      'settings' => array(
        'rows' => 20,
        'summary_rows' => 5,
      ),
      'type' => 'text_textarea_with_summary',
      'weight' => 2,
    ),
  );

  // Exported field_instance: 'node-picture-field_deninet6_nid'
  $field_instances['node-picture-field_deninet6_nid'] = array(
    'bundle' => 'picture',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'The old deninet v6 and earlier NID. Leave blank if this is new node created on v7.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 2,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 2,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_deninet6_nid',
    'label' => 'deninet6_nid',
    'required' => 0,
    'settings' => array(
      'max' => '',
      'min' => '',
      'prefix' => '',
      'suffix' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'number',
      'settings' => array(),
      'type' => 'number',
      'weight' => 4,
    ),
  );

  // Exported field_instance: 'node-picture-field_picture_file'
  $field_instances['node-picture-field_picture_file'] = array(
    'bundle' => 'picture',
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'galleryformatter',
        'settings' => array(
          'link_to_full' => 1,
          'link_to_full_style' => 0,
          'linking_method' => 'show_full_link',
          'modal' => 'none',
          'slide_style' => 'galleryformatter_slide',
          'style' => 'Greenarrows',
          'thumb_style' => 'galleryformatter_thumb',
        ),
        'type' => 'galleryformatter_default',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'hidden',
        'module' => 'galleryformatter',
        'settings' => array(
          'link_to_full' => 1,
          'link_to_full_style' => 0,
          'linking_method' => 'show_full_link',
          'modal' => 'none',
          'slide_style' => 'galleryformatter_slide',
          'style' => 'Greenarrows',
          'thumb_style' => 'galleryformatter_thumb',
        ),
        'type' => 'galleryformatter_default',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_picture_file',
    'label' => 'picture_file',
    'required' => 1,
    'settings' => array(
      'alt_field' => 0,
      'default_image' => 0,
      'file_directory' => 'uid-[current-user:uid]/picture/[current-date:custom:Ymd]',
      'file_extensions' => 'png gif jpg jpeg svg',
      'max_filesize' => '',
      'max_resolution' => '',
      'min_resolution' => '',
      'title_field' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'image',
      'settings' => array(
        'preview_image_style' => 'medium',
        'progress_indicator' => 'throbber',
      ),
      'type' => 'image_image',
      'weight' => 1,
    ),
  );

  // Exported field_instance: 'node-picture-field_tags'
  $field_instances['node-picture-field_tags'] = array(
    'bundle' => 'picture',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'taxonomy',
        'settings' => array(),
        'type' => 'taxonomy_term_reference_link',
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
    'field_name' => 'field_tags',
    'label' => 'tags',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'taxonomy',
      'settings' => array(
        'autocomplete_path' => 'taxonomy/autocomplete',
        'size' => 60,
      ),
      'type' => 'taxonomy_autocomplete',
      'weight' => 3,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Body');
  t('The old deninet v6 and earlier NID. Leave blank if this is new node created on v7.');
  t('deninet6_nid');
  t('picture_file');
  t('tags');

  return $field_instances;
}
