# -*- coding: utf-8 -*-
import scrapy
from scrapy.spiders import CrawlSpider, Rule
from scrapy.linkextractors import LinkExtractor

from scrapy.selector import Selector
from scrapy.item import Item
from scrapy_splash import SplashRequest

# User defined item
from real_estate.items import RealEstateItem
from pprint import pprint


class Dev00Spider(scrapy.Spider):
    name = "dev00"
    allowed_domains = ["batdongsan.com.vn"]
    base_url = "http://batdongsan.com.vn"
    ls_cat = [
        "/nha-dat-ban",
        "/nha-dat-cho-thue",
        "/du-an-bat-dong-san",
        "/can-mua",
        "/can-thue",
    ]
    
    start_urls = [
        base_url+"/nha-dat-ban",
        base_url+"/nha-dat-cho-thue",
        base_url+"/du-an-bat-dong-san",
        base_url+"/can-mua",
        base_url+"/can-thue",
    ]

    rules = [Rule(LinkExtractor(), callback="parse", follow=True)]
    items = {}

    def start_requests(self):
        """
        Only called once, overwrite to modify start_urls
        """
        ls_page = [""] + ["/p%d"%d for d in range(1, 10)]
        for url in self.start_urls:
            for page in ls_page:
                yield scrapy.Request(
                    url=url+page, callback=self.parse  #, endpoint="render.html"
                )

    def parse(self, response):
        # Get all the link from main page
        links = response.xpath("//div[@class='p-title']/h3/a/@href").extract()
        for link in links:
            full_link = self.base_url + link
            print(full_link)
            # Follow each link
            # yield scrapy.Request(full_link, callback=self.parse_item)
            yield SplashRequest( # need to wait 0.5 to allow javascript to run
                url=full_link, callback=self.parse_item, args={'wait': 1.5},
                endpoint="render.html"
            )
        print("=" * 50)

    def format_string(self, lsExtract):
        """
        Format to clean out \r\n\t and empty space in extracted items
        """
        trans_table = {ord(c): None for c in u'\r\n\t'}
        return " ".join([s.strip().translate(trans_table) for s in lsExtract])

    def parse_item(self, response):
        # Parse the information from response to item
        
        full_link = response.url
        cat = full_link.split("/")[-1].replace("-", "")
        # print(cat)
        title = response.xpath("//div[@class='pm-title']/h1/text()").extract()
        price = response.xpath(
            "//span[@class='gia-title mar-right-15']/strong/text()"
        ).extract()
        square = response.xpath(
            "//span[@class='gia-title']/strong/text()"
        ).extract()
        desc = response.xpath("//div[@class='pm-desc']/text()").extract()
        phones = response.xpath(
            "//span[@class='hidden-phone hidden-mobile detail']/@raw"
        ).extract()  # Try to extract all phone number here
        # print(title)
        # print(price)
        # print(square)
        # print(desc)
        # print(phones)
        # Add extracted value to item
        item = RealEstateItem()
        item["title"] = self.format_string(title)
        item["price"] = self.format_string(price)
        item["square"] = self.format_string(square)
        item["desc"] = self.format_string(desc)
        item["phones"] = phones
        item["link"] = full_link
        pprint(item)
        yield item
        # Add item data to dict
        if cat not in self.items.keys():
            self.items[cat] = list()
        self.items[cat].append(item)
        # links = response.xpath('//a/@href').extract()

        # # We stored already crawled links in this list
        # crawledLinks = []

        # # Pattern to check proper link
        # # I only want to get tutorial posts
        # linkPattern = re.compile("^\/tutorials\?page=\d+")

        # for link in links:
        # # If it is a proper link and is not checked yet, yield it to the Spider
        #     if linkPattern.match(link) and not link in crawledLinks:
        #         link = self.base_url + link
        #         crawledLinks.append(link)
        #         yield Request(link, self.parse)

        # titles = response.xpath('//a[contains(@class, "posts__post-title")]/h1/text()').extract()
        # for title in titles:
        #     item = RealEstateItem()
        #     item["title"] = title
        #     yield item
