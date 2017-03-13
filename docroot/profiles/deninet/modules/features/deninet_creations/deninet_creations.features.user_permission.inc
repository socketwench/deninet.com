<?php
/**
 * @file
 * deninet_creations.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function deninet_creations_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create creation content'.
  $permissions['create creation content'] = array(
    'name' => 'create creation content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete any creation content'.
  $permissions['delete any creation content'] = array(
    'name' => 'delete any creation content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete own creation content'.
  $permissions['delete own creation content'] = array(
    'name' => 'delete own creation content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'edit any creation content'.
  $permissions['edit any creation content'] = array(
    'name' => 'edit any creation content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'edit own creation content'.
  $permissions['edit own creation content'] = array(
    'name' => 'edit own creation content',
    'roles' => array(),
    'module' => 'node',
  );

  return $permissions;
}
