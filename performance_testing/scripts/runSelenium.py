import sys
import time

from selenium import webdriver
from selenium.webdriver.chrome.options import Options

options = Options()
options.add_argument('--headless')
options.add_argument('--no-sandbox')
options.add_argument('--disable-gpu')
options.add_argument('--disable-dev-shm-usage')
driver = webdriver.Chrome(executable_path='/selenium-drivers/chromedriver', options=options)
print ("Headless Chrome Initialized")
driver.get('http://localhost:8081/recordings')


if sys.argv[1] == 'memory':
    print("Setting up memory")
    driver.find_element_by_xpath('//*[@title="Replay '+sys.argv[2]+'."]').click()
    time.sleep(5)
    driver.find_element_by_xpath('//*[@id="playButton"]').click()
    print("Completing memory init")
    driver.quit()
    sys.exit()
else:
    print("\nRunning file: " + sys.argv[1])
    driver.find_element_by_xpath('//*[@title="Replay '+sys.argv[1]+'."]').click()

timeStart = driver.find_element_by_xpath('//*[@id="containerTimeStampUnix"]').text
time.sleep(2)

while timeStart != driver.find_element_by_xpath('//*[@id="containerTimeStampUnix"]').text:
    timeStart = driver.find_element_by_xpath('//*[@id="containerTimeStampUnix"]').text
    time.sleep(2)

print("Last timestamp " + driver.find_element_by_xpath('//*[@id="containerTimeStampUnix"]').text)

driver.quit()
sys.exit()
