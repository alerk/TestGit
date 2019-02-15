from bs4 import BeautifulSoup
import requests

html = requests.get("http://www.example.com").text
soup = BeautifulShoup(html, "html5lib")

first_paragraph = soup.find("p") #or just soup.p

first_paragraph_text = soup.p.text
first_paragraph_words = soup.p.text.split()
