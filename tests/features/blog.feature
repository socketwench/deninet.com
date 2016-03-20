@api @feature_blog
  Feature: As a site user, I would like per-user blogs.

    Scenario: As a site user, I would like my own blog page associated with my user.
      Given I am logged in as a user with the "administrator" role
      And I am on "blogs/admin"
      Then I should see "admin's blog"