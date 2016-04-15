<?php
/**
 * @file
 * deninet_demo_link.features.uuid_node.inc
 */

/**
 * Implements hook_uuid_features_default_content().
 */
function deninet_demo_link_uuid_features_default_content() {
  $nodes = array();

  $nodes[] = array(
  'uid' => 1,
  'title' => 'Example Link',
  'log' => '',
  'status' => 1,
  'comment' => 2,
  'promote' => 1,
  'sticky' => 0,
  'vuuid' => 'f290d5ab-c678-4582-ac9a-8eb11dc89319',
  'type' => 'link',
  'language' => 'und',
  'created' => 1459388486,
  'tnid' => 0,
  'translate' => 0,
  'uuid' => '76d8d381-9ffa-4d2f-8756-a67211feb09e',
  'revision_uid' => 1,
  'body' => array(
    'und' => array(
      0 => array(
        'value' => 'Whenever you need to refer to a canonical URL that the TLDs haven\'t given away yet, example.com is there.',
        'summary' => '',
        'format' => 'filtered_html',
        'safe_value' => '<p>Whenever you need to refer to a canonical URL that the TLDs haven\'t given away yet, example.com is there.</p>
',
        'safe_summary' => '',
      ),
    ),
  ),
  'field_tags' => array(
//    'und' => array(
//      0 => array(
//        'tid' => 10,
//        'uuid' => 'bb2c350d-3279-41c5-9030-1e09a6d36d0d',
//      ),
//    ),
  ),
  'field_topic' => array(
    'und' => array(
      0 => array(
//        'tid' => 2,
        'uuid' => 'bf722a4b-5729-404f-9a7f-e8a20b0d4610',
      ),
    ),
  ),
  'field_url' => array(
    'und' => array(
      0 => array(
        'value' => 'http://example.com',
        'title' => 'Example Domain',
        'attributes' => array(),
      ),
    ),
  ),
  'path' => array(
    'pathauto' => 1,
  ),
  'cid' => 0,
  'last_comment_name' => NULL,
  'last_comment_uid' => 1,
  'comment_count' => 0,
  'flag_friend_access' => FALSE,
  'name' => 'admin',
  'picture' => 0,
  'data' => 'b:0;',
  'pathauto_perform_alias' => FALSE,
  'date' => '2016-03-31 01:41:26 +0000',
);
  return $nodes;
}
