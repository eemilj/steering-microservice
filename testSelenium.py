import sys

from selenium import webdriver
from selenium.webdriver.chrome.options import Options

options = Options()
options.add_argument('--headless')
driver = webdriver.Chrome(executable_path='chromedriver', options=options)
print ("Headless Chrome Initialized")
driver.get('http://www.google.com')
print ("Headless Chrome finished")
driver.quit()
sys.exit()

