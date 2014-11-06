<?php
/**
 * @file
 * deninet_picture.features.inc
 */

/**
 * Implements hook_node_info().
 */
function deninet_picture_node_info() {
  $items = array(
    'picture' => array(
      'name' => t('Picture'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
