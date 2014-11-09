<?php
/**
 * @file
 * deninet_blog.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function deninet_blog_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
