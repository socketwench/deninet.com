@api @feature_link
Feature: As a site user, I would like to share links.

  Scenario: As a site user, I would like to share links with commentary.
    Given I am logged in as a user with the "administrator" role
    And I am on "node/add/link"
    Then I should see "Create Link"

  Scenario:
    Given I am an anonymous user
    And I am on "content/example-link"
    Then I should see "Example Link"
    And I should see "Example Domain"