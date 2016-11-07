<?php

$databases = array (
  'default' =>
  array (
    'default' =>
    array (
      'database' => $_ENV['MYSQL_DATABASE'],
      'username' => $_ENV['MYSQL_USER'],
      'password' => $_ENV['MYSQL_PASSWORD'],
      'host' => 'db',
      'port' => '',
      'driver' => 'mysql',
      'prefix' => '',
    ),
  ),
);

/**
 * Settings for stage_file_proxy.module.
 */
$conf['stage_file_proxy_origin'] = 'https://www.deninet.com';
$conf['stage_file_proxy_origin_dir'] = 'files';
$conf['stage_file_proxy_hotlink'] = TRUE;
$conf['stage_file_proxy_sslversion'] = '3';

/**
 * Varnish configuration.
 */
$conf['cache_backends'] = array('profiles/deninet/modules/contrib/varnish/varnish.cache.inc');
$conf['cache_class_cache_page'] = 'VarnishCache';
$conf['page_cache_invoke_hooks'] = FALSE;
$conf['varnish_version'] = '4';
$conf['varnish_control_terminal'] = 'varnish:6082';
$conf['varnish_control_key'] = $_ENV['VARNISH_SECRET'];
$conf['varnish_bantype'] = 1;

/**
 * Memcache configuration.
 */
$conf['memcache_extension'] = 'Memcached';
$conf['cache_backends'][] = 'profiles/deninet/modules/contrib/memcache_storage/memcache_storage.inc';
$conf['cache_default_class'] = 'MemcacheStorage';
$conf['cache_class_cache_form'] = 'DrupalDatabaseCache';
$conf['cache_class_cache_update'] = 'DrupalDatabaseCache';
$conf['lock_inc'] = 'profiles/deninet/modules/contrib/memcache_storage/includes/lock.inc';
$conf['memcache_storage_persistent_connection'] = TRUE;
$conf['memcache_storage_key_prefix'] = 'stillwaterschools';
$conf['memcache_servers'] = array(
  'memcache:11211' => 'default',
);
$conf['memcache_storage_compress_data'] = TRUE;
