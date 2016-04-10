<?php
/**
 * @file
 * deninet_blocks.features.fe_block_boxes.inc
 */

/**
 * Implements hook_default_fe_block_boxes().
 */
function deninet_blocks_default_fe_block_boxes() {
  $export = array();

  $fe_block_boxes = new stdClass();
  $fe_block_boxes->info = 'Footer message';
  $fe_block_boxes->format = 'filtered_html';
  $fe_block_boxes->machine_name = 'de_footer_message';
  $fe_block_boxes->body = '<p>deninet 7.5 ©1999-2016&nbsp;denizen entertainment. All content property of the original poster unless otherwise stated (or obvious).</p>
';

  $export['de_footer_message'] = $fe_block_boxes;

  return $export;
}
