<?php
/**
 * @file
 * deninet_paragraphs.features.inc
 */

/**
 * Implements hook_paragraphs_info().
 */
function deninet_paragraphs_paragraphs_info() {
  $items = array(
    'audio_playlist' => array(
      'name' => 'Audio Playlist',
      'bundle' => 'audio_playlist',
      'locked' => '1',
    ),
    'image_gallery' => array(
      'name' => 'Image Gallery',
      'bundle' => 'image_gallery',
      'locked' => '1',
    ),
    'simple_text' => array(
      'name' => 'Simple text',
      'bundle' => 'simple_text',
      'locked' => '1',
    ),
  );
  return $items;
}
