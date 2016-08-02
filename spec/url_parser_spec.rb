require 'spec_helper'
require 'url_parser'

describe UrlParser do
  describe "#valid" do
    it "for valid URL" do
      UrlParser::Url.new('http')
      expect(true).to be_falsey
    end
  end
end
