import sys

from selenium import webdriver
from selenium.webdriver.chrome.options import Options

options = Options()
options.add_argument('--headless')
options.add_argument('--no-sandbox')
options.add_argument('--disable-gpu')
driver = webdriver.Chrome(executable_path='/selenium-drivers/chromedriver', options=options)
print ("Headless Chrome Initialized")
driver.get('http://www.google.com')
driver.quit()
sys.exit()
