<?php
/**
 * @file
 * deninet_picture.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function deninet_picture_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create picture content'.
  $permissions['create picture content'] = array(
    'name' => 'create picture content',
    'roles' => array(
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any picture content'.
  $permissions['delete any picture content'] = array(
    'name' => 'delete any picture content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own picture content'.
  $permissions['delete own picture content'] = array(
    'name' => 'delete own picture content',
    'roles' => array(
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any picture content'.
  $permissions['edit any picture content'] = array(
    'name' => 'edit any picture content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own picture content'.
  $permissions['edit own picture content'] = array(
    'name' => 'edit own picture content',
    'roles' => array(
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  return $permissions;
}
