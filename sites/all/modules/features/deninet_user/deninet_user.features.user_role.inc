<?php
/**
 * @file
 * deninet_user.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function deninet_user_user_default_roles() {
  $roles = array();

  // Exported role: staff.
  $roles['staff'] = array(
    'name' => 'staff',
    'weight' => 3,
  );

  return $roles;
}
