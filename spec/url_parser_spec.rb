require 'spec_helper'
require 'url_parser'

describe UrlParser::URL do
  context 'valid URL' do
    subject (:url){ UrlParser::URL.new('https://alice:secret@example.com:80/path/index.php?filter=employee#first_name') }
    it { is_expected.to be_valid }
    describe "#scheme" do
      it { expect(url.scheme).to eql 'https' }
    end

    describe "#userinfo" do
      it { expect(url.userinfo).to eql 'alice:secret' }
    end

    describe "#host" do
      it { expect(url.host).to eql 'example.com' }
    end

    describe "#host_type" do
      it { expect(url.host_type).to be :REGNAME }
    end

    describe "#port" do
      it { expect(url.port).to be 80 }
    end

    describe "#path" do
      it { expect(url.path).to eql '/path/index.php' }
    end

    describe "#query" do
      it { expect(url.query).to eql 'filter=employee' }
    end

    describe "#fragment" do
      it { expect(url.fragment).to eql 'first_name' }
    end
  end
end
