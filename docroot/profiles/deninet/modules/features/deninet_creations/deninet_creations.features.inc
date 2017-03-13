<?php
/**
 * @file
 * deninet_creations.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function deninet_creations_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function deninet_creations_node_info() {
  $items = array(
    'creation' => array(
      'name' => t('Creation'),
      'base' => 'node_content',
      'description' => t('A piece of art, writing, music, video, or other creation. '),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
