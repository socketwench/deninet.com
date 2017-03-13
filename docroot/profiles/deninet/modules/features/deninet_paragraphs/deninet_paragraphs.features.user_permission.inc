<?php
/**
 * @file
 * deninet_paragraphs.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function deninet_paragraphs_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'administer paragraphs bundles'.
  $permissions['administer paragraphs bundles'] = array(
    'name' => 'administer paragraphs bundles',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'paragraphs',
  );

  return $permissions;
}
