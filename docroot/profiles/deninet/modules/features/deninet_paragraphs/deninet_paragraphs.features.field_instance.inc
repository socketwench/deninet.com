<?php
/**
 * @file
 * deninet_paragraphs.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function deninet_paragraphs_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance:
  // 'paragraphs_item-audio_playlist-field_audio_playlist'.
  $field_instances['paragraphs_item-audio_playlist-field_audio_playlist'] = array(
    'bundle' => 'audio_playlist',
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'file',
        'settings' => array(),
        'type' => 'file_default',
        'weight' => 0,
      ),
      'paragraphs_editor_preview' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'paragraphs_item',
    'field_name' => 'field_audio_playlist',
    'label' => 'Audio Playlist',
    'required' => 1,
    'settings' => array(
      'description_field' => 0,
      'file_directory' => 'uid-[current-user:uid]/audio/[current-date:custom:Ymd]',
      'file_extensions' => 'mp3 m4a ogg',
      'max_filesize' => '100 MB',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'media',
      'settings' => array(
        'allowed_schemes' => array(
          'public' => 'public',
        ),
        'allowed_types' => array(
          'audio' => 0,
          'default' => 0,
          'image' => 'image',
          'video' => 0,
        ),
        'progress_indicator' => 'throbber',
      ),
      'type' => 'media_generic',
      'weight' => 1,
    ),
  );

  // Exported field_instance: 'paragraphs_item-image_gallery-field_gallery'.
  $field_instances['paragraphs_item-image_gallery-field_gallery'] = array(
    'bundle' => 'image_gallery',
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
      'paragraphs_editor_preview' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'paragraphs_item',
    'field_name' => 'field_gallery',
    'label' => 'Gallery',
    'required' => 1,
    'settings' => array(
      'alt_field' => 0,
      'default_image' => 0,
      'file_directory' => 'uid-[current-user:uid]/picture/[current-date:custom:Ymd]',
      'file_extensions' => 'png gif jpg jpeg svg',
      'max_filesize' => '',
      'max_resolution' => '',
      'min_resolution' => '',
      'title_field' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'media',
      'settings' => array(
        'allowed_schemes' => array(
          'public' => 'public',
        ),
        'allowed_types' => array(
          0 => 0,
          'audio' => 0,
          'default' => 0,
          'image' => 'image',
          'video' => 0,
        ),
        'progress_indicator' => 'throbber',
      ),
      'type' => 'media_generic',
      'weight' => 1,
    ),
  );

  // Exported field_instance: 'paragraphs_item-simple_text-field_para_text'.
  $field_instances['paragraphs_item-simple_text-field_para_text'] = array(
    'bundle' => 'simple_text',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 0,
      ),
      'paragraphs_editor_preview' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'paragraphs_item',
    'field_name' => 'field_para_text',
    'label' => 'Text',
    'required' => 1,
    'settings' => array(
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 5,
      ),
      'type' => 'text_textarea',
      'weight' => 1,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Audio Playlist');
  t('Gallery');
  t('Text');

  return $field_instances;
}
