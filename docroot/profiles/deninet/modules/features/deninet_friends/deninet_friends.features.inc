<?php
/**
 * @file
 * deninet_friends.features.inc
 */

/**
 * Implements hook_views_api().
 */
function deninet_friends_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_flag_default_flags().
 */
function deninet_friends_flag_default_flags() {
  $flags = array();
  // Exported flag: "Friend".
  $flags['friend'] = array(
    'entity_type' => 'user',
    'title' => 'Friend',
    'global' => 0,
    'types' => array(),
    'flag_short' => 'Add friend',
    'flag_long' => 'Add this user to your list of friends.',
    'flag_message' => '',
    'unflag_short' => 'Remove friend',
    'unflag_long' => 'Remove this user from your list of friends.',
    'unflag_message' => '',
    'unflag_denied_text' => '',
    'link_type' => 'confirm',
    'weight' => 0,
    'show_in_links' => array(),
    'show_as_field' => FALSE,
    'show_on_form' => 0,
    'access_author' => '',
    'show_contextual_link' => FALSE,
    'show_on_profile' => 1,
    'access_uid' => 'others',
    'flag_confirmation' => 'Are you sure you want to add [user:name] to your list of friends?',
    'unflag_confirmation' => 'Are you sure you want to remove [user:name] from your list of friends?',
    'module' => 'deninet_friends',
    'locked' => array(
      0 => 'name',
    ),
    'api_version' => 3,
  );
  return $flags;

}
