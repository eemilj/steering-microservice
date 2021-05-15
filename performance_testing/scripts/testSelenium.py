import sys

from selenium import webdriver

chrome_options = webdriver.ChromeOptions()
chrome_options.add_argument('--no-sandbox')
chrome_options.add_argument('--headless')
chrome_options.add_argument('--disable-gpu')
driver = webdriver.Chrome(executable_path='/selenium-drivers/chromedriver', chrome_options=chrome_options)
print ("Headless Chrome Initialized")
driver.get('https://www.google.com')
print ("Headless Chrome finished")
driver.quit()
sys.exit()

