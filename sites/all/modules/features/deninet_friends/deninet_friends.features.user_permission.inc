<?php
/**
 * @file
 * deninet_friends.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function deninet_friends_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'administer flags'.
  $permissions['administer flags'] = array(
    'name' => 'administer flags',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'flag',
  );

  // Exported permission: 'flag friend'.
  $permissions['flag friend'] = array(
    'name' => 'flag friend',
    'roles' => array(
      'staff' => 'staff',
    ),
    'module' => 'flag',
  );

  // Exported permission: 'receive friend email notification'.
  $permissions['receive friend email notification'] = array(
    'name' => 'receive friend email notification',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'flag_friend',
  );

  // Exported permission: 'unflag friend'.
  $permissions['unflag friend'] = array(
    'name' => 'unflag friend',
    'roles' => array(
      'staff' => 'staff',
    ),
    'module' => 'flag',
  );

  // Exported permission: 'use flag import'.
  $permissions['use flag import'] = array(
    'name' => 'use flag import',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'flag',
  );

  return $permissions;
}
