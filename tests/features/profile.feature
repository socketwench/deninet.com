@api
Feature: As a site developer, I want to validate default profile configurations.

  Scenario: As a site admin, I need the sitewide configuration feature enabled post-install.
    Given I am logged in as a user with the "administrator" role
    And I am on "admin/modules"
    Then the "edit-modules-deninet-deninet-sitewide-config-enable" checkbox should be checked