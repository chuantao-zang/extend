#
# Be sure to run `pod lib lint extend.podspec' to ensure this is a
# valid spec before submitting.
#
# Any lines starting with a # are optional, but their use is encouraged
# To learn more about a Podspec see https://guides.cocoapods.org/syntax/podspec.html
#

Pod::Spec.new do |s|
  s.name             = 'extend'
  s.version          = '0.1.0'
  s.summary          = 'Inpixon Extend Framework.'

# This description is used to generate tags and improve search results.
#   * Think: What does it do? Why did you write it? What is the focus?
#   * Try to keep it short, snappy and to the point.
#   * Write the description between the DESC delimiters below.
#   * Finally, don't worry about the indent, CocoaPods strips it!

  s.description      ='This library provides indoor location update.'

  s.homepage         = 'https://github.com/chuantao-zang/extend.pod'
  # s.screenshots     = 'www.example.com/screenshots_1', 'www.example.com/screenshots_2'
  s.license          = { :type => 'MIT', :file => 'LICENSE' }
  s.author           = { 'chuantao-zang' => 'chuantao.zang@inpixon.com' }
  s.source           = { :git => 'https://github.com/chuantao-zang/extend.pod.git', :tag => s.version.to_s }
  # s.social_media_url = 'https://twitter.com/<TWITTER_USERNAME>'

  s.ios.deployment_target = '9.0'

  s.source_files = 'extend/Classes/**/*'
  
  # s.resource_bundles = {
  #   'extend' => ['extend/Assets/*.png']
  # }

  # s.public_header_files = 'Pod/Classes/**/*.h'
  # s.frameworks = 'UIKit', 'MapKit'
  s.vendored_framework = 'extend/Frameworks/extend.framework'
  s.swift_versions = '5.0'
  # s.dependency 'AFNetworking', '~> 2.3'
end
