import xmltodict
import pandas as pd
import datetime
from pprint import pprint

def structure_data():
    xml_file_path = 'data/studies.xml'
    with open(xml_file_path, 'r') as f:
        data = f.read()
    # write your solution here
    # Extract information in <ce:doi>, <publicationdate>, <titletext>, <ce:para> tag
    # and store them in a pandas dataframe
    dict_data = xmltodict.parse(data)
    print(f"len(dict_data): {len(dict_data)}")
    ls_records = list()
    for _, v in dict_data.items():
        item_data = v["item"]
        # print(f"len(item_data): {len(item_data)}")
        # print(f"type(item_data): {type(item_data)}")
        for item in item_data:
            bibrecord = item["bibrecord"]
            publicationdate = bibrecord["head"]["source"]["publicationdate"]
            doi = bibrecord["item-info"]["itemidlist"]["ce:doi"]
            y_m_d = datetime.date(
                year=int(publicationdate["year"]),
                month=int(publicationdate["month"]),
                day=int(publicationdate["day"])
            ).strftime("%Y-%m-%d")
            title = bibrecord["head"]["citation-title"]["titletext"]["#text"]
            abstract = bibrecord["head"]["abstracts"]["abstract"]["ce:para"]
            ls_records.append((doi, y_m_d, title, abstract))
    df_data = pd.DataFrame(columns=['doi', 'publication_date', 'title', 'abstract'], data=ls_records)

    return df_data


if __name__ == "__main__":
    structure_data()

# {
#     'ait:process-info': {
#         'ait:date-delivered': {'@year': '2012', '@month': '10', '@day': '16'},
#         'ait:date-sort': {'@year': '2008', '@month': '03', '@day': '01'},
#         'ait:status': {'@type': 'core', '@state': 'backfile_new', '@stage': 'S300'}
#     }, 
#     'bibrecord': {
#         'item-info': {
#             'itemidlist': {
#                 'ce:doi': '10.1007/s00431-007-0495-y', # <-- Extract this ["bibrecord"]["item-info"]["itemidlist"]["ce:doi"]
#                 'itemid': [
#                     {'@idtype': 'PUI', '#text': '351238211'},
#                     {'@idtype': 'MEDL', '#text': '17516086'}]
#             },
#             'history': {
#                 'date-created': {'@year': '2021', '@month': '03', '@day': '13'}, 
#                 'date-aip-loaded': {'@year': '2021', '@month': '03', '@day': '16'}, 
#                 'date-loaded': {'@year': '2021', '@month': '03', '@day': '16'}
#             }, 
#             'dbcollection': 'MEDL'
#         }, 
#         'head': {
#             'citation-info': {'citation-type': {'@code': 'ar'}, 'citation-language': {'@xml:lang': 'eng'}, 'abstract-language': {'@xml:lang': 'eng'}, 'author-keywords': {'author-keyword': ['Chair-rising test', 'Maximal isometric grip force', 'Peak jump force', 'Peak jump power']}}, 
#             'citation-title': {
#                 'titletext': {
#                     '@xml:lang': 'eng', '@original': 'y',
#                     '#text': 'Mechanographic characteristics of adolescents and young adults with congenital heart disease' # <-- Extract this ["bibrecord"]["head"]["citation-title"]["titletext"]["#text"]
#                 }
#             }, 
#             'author-group': [{'author': [{'@seq': '1', '@type': 'auth', 'ce:initials': 'O.', 'ce:indexed-name': 'Fricke O.', 'ce:surname': 'Fricke', 'ce:given-name': 'Oliver', 'ce:e-address': 'frickeo@uni-koeln.de'}, {'@seq': '6', '@type': 'auth', 'ce:initials': 'E.', 'ce:indexed-name': 'Schoenau E.', 'ce:surname': 'Schoenau', 'ce:given-name': 'Eckhard'}], 'affiliation': {'@country': 'deu', 'organization': 'One hospital', 'address-part': 'Kerpenerstr. 62', 'city-group': 'D-50924 Cologne'}}, {'author': [{'@seq': '2', '@type': 'auth', 'ce:initials': 'C.', 'ce:indexed-name': 'Witzel C.', 'ce:surname': 'Witzel', 'ce:given-name': 'Cordelia'}, {'@seq': '3', '@type': 'auth', 'ce:initials': 'S.', 'ce:indexed-name': 'Schickendantz S.', 'ce:surname': 'Schickendantz', 'ce:given-name': 'Sabine'}, {'@seq': '4', '@type': 'auth', 'ce:initials': 'N.', 'ce:indexed-name': 'Sreeram N.', 'ce:surname': 'Sreeram', 'ce:given-name': 'Narayanswami'}, {'@seq': '5', '@type': 'auth', 'ce:initials': 'K.', 'ce:indexed-name': 'Brockmeier K.', 'ce:surname': 'Brockmeier', 'ce:given-name': 'Konrad'}], 'affiliation': {'@country': 'deu', 'organization': 'And the other', 'city-group': 'Cologne'}}], 
#             'correspondence': {'person': {'ce:initials': 'O.', 'ce:indexed-name': 'Fricke O.', 'ce:surname': 'Fricke'}, 'affiliation': {'@country': 'deu', 'organization': "Children's Hospital, University of Cologne", 'address-part': 'Kerpenerstr. 62', 'city-group': 'D-50924 Cologne'}, 'ce:e-address': 'frickeo@uni-koeln.de'}, 
#             'abstracts': {
#                 'abstract': {
#                     '@original': 'y',
#                     'ce:para': ''  # <-- Extract this: ["head"]["abstracts"]["abstract"]["ce:para"]
#                 }
#             }, 
#             'source': {
#                 '@type': 'j', '@country': 'usa', 'sourcetitle': 'Annals of Pharmacotherapy', 'sourcetitle-abbrev': 'Ann. Pharmacother.', 'issn': {'@type': 'print', '#text': '10600280'}, 'codencode': 'APHRE', 'volisspag': {'voliss': {'@volume': '42', '@issue': '2'}, 'pagerange': {'@first': '259', '@last': '264'}}, 'publicationyear': {'@first': '2008'}, 
#                 'publicationdate': {'year': '2008', 'month': '02', 'day': '05'},  # <-- Extract this  ["head"]["source"]["publicationdate"]
#                 'publisher': {'publishername': 'Harvey Whitney Books Company', 'affiliation': {'@country': 'usa', 'address-part': '8044 Montgomery Road, Suite 415', 'city': 'Cincinnati', 'postal-code': 'OH 45236'}}},
#              'enhancement': None
#         },
#         'tail': {
#             'bibliography': {'@refcount': '40'}
#         }
#     }
# },
# {
#     'ait:process-info': {'ait:date-delivered': {'@year': '2012', '@month': '10', '@day': '16'}, 'ait:date-sort': {'@year': '2008', '@month': '01', '@day': '01'}, 'ait:status': {'@type': 'core', '@state': 'backfile_new', '@stage': 'S300'}}, 'bibrecord': {'item-info': {'itemidlist': {'ce:doi': '10.1586/17474108.3.1.33', 'itemid': {'@idtype': 'PUI', '#text': '351227617'}}, 'history': {'date-created': {'@year': '2008', '@month': '01', '@day': '01'}, 'date-aip-loaded': {'@year': '2008', '@month': '01', '@day': '01'}}}, 'head': {'citation-info': {'citation-type': {'@code': 'cp'}, 'citation-language': {'@xml:lang': 'eng'}, 'abstract-language': {'@xml:lang': 'eng'}}, 'citation-title': {'titletext': {'@xml:lang': 'eng', '@original': 'y', '#text': 'Women deliver: A global conference'}}, 'author-group': {'author': {'@seq': '1', '@type': 'auth', 'ce:initials': 'F.A.', 'ce:indexed-name': 'Donnay F.A.', 'ce:surname': 'Donnay', 'ce:given-name': 'France A.', 'ce:e-address': 'france.donnay@un.org.pk'}}, 'correspondence': {'person': {'ce:initials': 'F.A.', 'ce:indexed-name': 'Donnay F.A.', 'ce:surname': 'Donnay'}, 'affiliation': {'@country': 'pak', 'organization': 'United Nations Population Fund (UNFPA)', 'address-part': 'Street 17, Sector F-712', 'city-group': 'Islamabad'}, 'ce:e-address': 'france.donnay@un.org.pk'}, 'abstracts': {'abstract': {'@original': 'y', 
#     'ce:para': ""}},'source': {'@type': 'j', '@country': 'gbr', 'sourcetitle': 'Expert Review of Obstetrics and Gynecology', 'sourcetitle-abbrev': 'Expert Rev. Obstet. Gynecol.', 'issn': {'@type': 'print', '#text': '17474108'}, 'volisspag': {'voliss': {'@volume': '3', '@issue': '1'}, 'pagerange': {'@first': '33', '@last': '34'}}, 'publicationyear': {'@first': '2008'}, 'publicationdate': {'year': '2008', 'month': '01', 'day': '12'}, 'publisher': {'publishername': 'Expert Reviews Ltd.', 'affiliation': {'@country': 'gbr', 'address-part': '2 Albert Place', 'city': 'London', 'postal-code': 'N3 1QB'}}}, 'enhancement': {'descriptorgroup': {'descriptors': {'@controlled': 'y', '@type': 'MED', 'descriptor': [{'mainterm': 'Africa'}, {'mainterm': 'conference paper'}, {'mainterm': {'@weight': 'a', '#text': 'delivery'}}, {'mainterm': 'whole body PET'}, {'mainterm': 'whole body MRI'}, {'mainterm': 'ion mobility spectrometry-mass spectrometry'}, {'mainterm': 'maternal mortality'}, {'mainterm': 'maternal welfare'}, {'mainterm': 'morbidity'}, {'mainterm': 'newborn mortality'}, {'mainterm': 'politics'}, {'mainterm': 'South Asia'}, {'mainterm': 'United Kingdom'}, {'mainterm': 'United Nations'}, {'mainterm': {'@weight': 'a', '#text': "women's health"}}, {'mainterm': 'world health organization'}]}}, 'classificationgroup': {'classifications': {'@type': 'EMCLASS', 'classification': [{'classification-code': '10', 'classification-description': 'Obstetrics and Gynecology'}, {'classification-code': '17', 'classification-description': 'Public Health, Social Medicine and Epidemiology'}]}}}}}}, {'ait:process-info': {'ait:date-delivered': {'@year': '2012', '@month': '10', '@day': '16'}, 'ait:date-sort': {'@year': '2008', '@month': '03', '@day': '20'}, 'ait:status': {'@type': 'core', '@state': 'backfile_new', '@stage': 'S300'}}, 'bibrecord': {'item-info': {'itemidlist': {'ce:pii': 'S092777570700917X', 'ce:doi': '10.1016/j.colsurfa.2007.10.012', 'itemid': {'@idtype': 'PUI', '#text': '351232199'}}, 'history': {'date-created': {'@year': '2008', '@month': '03', '@day': '03'}}}, 'head': {'citation-info': {'citation-type': {'@code': 'ar'}, 'citation-language': {'@xml:lang': 'eng'}, 'abstract-language': {'@xml:lang': 'eng'}, 'author-keywords': {'author-keyword': ['Biomineralization', 'Calcium oxalate', 'Defect', 'DPPC', 'Langmuir-Blodgett film']}}, 'citation-title': {'titletext': {'@xml:lang': 'eng', '@original': 'y', '#text': 'Formation of circular patterns of calcium oxalate crystals at defective sites of Langmuir-Blodgett films'}}, 'author-group': {'author': [{'@seq': '1', '@type': 'auth', 'ce:initials': 'J.-M.', 'ce:indexed-name': 'Ouyang J.-M.', 'ce:surname': 'Ouyang', 'ce:given-name': 'Jian-Ming', 'ce:e-address': 'toyjm@jnu.edu.cn'}, {'@seq': '2', '@type': 'auth', 'ce:initials': 'S.-P.', 'ce:indexed-name': 'Deng S.-P.', 'ce:surname': 'Deng', 'ce:given-name': 'Sui-Ping'}], 'affiliation': {'organization': 'Institute of Biomineralization and Lithiasis Research, Jinan University', 'city-group': 'Guangzhou, 510632'}}, 'correspondence': {'person': {'ce:initials': 'J.-M.', 'ce:indexed-name': 'Ouyang J.-M.', 'ce:surname': 'Ouyang'}, 'affiliation': {'@country': 'chn', 'organization': 'Institute of Biomineralization and Lithiasis Research, Jinan University', 'city-group': 'Guangzhou, 510632'}, 'ce:e-address': 'toyjm@jnu.edu.cn'}, 'abstracts': {'abstract': {'@original': 'y', 'ce:para': ''}
