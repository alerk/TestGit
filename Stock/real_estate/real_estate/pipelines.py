# -*- coding: utf-8 -*-
import json
# from scrapy.exporters import JSONItemExporter
import traceback, datetime
# Define your item pipelines here
#
# Don't forget to add your pipeline to the ITEM_PIPELINES setting
# See: https://docs.scrapy.org/en/latest/topics/item-pipeline.html


class RealEstatePipeline(object):
    """
    Distribute items to different files based on YYYYmm
    """
    exporter = None
    f = None

    # def close_spider(self, spider):
    #     if self.exporter is not None: # and type(exporter) == 
    #         self.exporter.finish_exporting()
    #     if self.f is not None:
    #         self.f.close()

    def process_item(self, item, spider):
        # Ym = datetime.datetime.now().strftime("%Y%m")
        # self.f = open("./{}.json".format(Ym), "w+b")
        # try:
        #     self.exporter = JSONItemExporter(f)
        #     self.exporter.start_exporting()
        #     self.exporter.export_item(item)
        # except ex:
        #     traceback.print_exc()

        return item
        
