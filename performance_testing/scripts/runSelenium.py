import sys
import time

from selenium import webdriver
from selenium.webdriver.chrome.options import Options

options = Options()
options.add_argument('--headless')
options.add_argument('--no-sandbox')
options.add_argument('--disable-gpu')
driver = webdriver.Chrome(executable_path='/selenium-drivers/chromedriver', options=options)
print ("Headless Chrome Initialized")
driver.get('http://localhost:8081/recordings')


if sys.argv[1] == '1':
    print("\nIteration: $i" + sys.argv[1])
    driver.find_element_by_xpath('//*[@title="Replay CID-140-recording-2020-03-18_144821-selection.rec."]').click()
    driver.implicitly_wait(2000)
elif sys.argv[1] == '2':
    print("\nIteration: $i" + sys.argv[1])
    driver.find_element_by_xpath('//*[@title="Replay CID-140-recording-2020-03-18_145043-selection.rec."]').click()
elif sys.argv[1] == '3':
    print("\nIteration: $i" + sys.argv[1])
    driver.find_element_by_xpath('//*[@title="Replay CID-140-recording-2020-03-18_145233-selection.rec."]').click()
elif sys.argv[1] == '4':
    print("\nIteration: $i" + sys.argv[1])
    driver.find_element_by_xpath('//*[@title="Replay CID-140-recording-2020-03-18_145641-selection.rec."]').click()
elif sys.argv[1] == '5':
    print("\nIteration: $i" + sys.argv[1])
    driver.find_element_by_xpath('//*[@title="Replay CID-140-recording-2020-03-18_150001-selection.rec."]').click()
elif sys.argv[1] == 'memory':
    print("\nIteration: $i" + sys.argv[1])
    driver.find_element_by_xpath('//*[@title="Replay CID-140-recording-2020-03-18_150001-selection.rec."]').click()
    time.sleep(5)
    driver.find_element_by_xpath('//*[@id="playButton"]').click()
    driver.quit()
    sys.exit()

timeStart = driver.find_element_by_xpath('//*[@id="containerTimeStampUnix"]').text
time.sleep(2)

while timeStart != driver.find_element_by_xpath('//*[@id="containerTimeStampUnix"]').text:
    print(timeStart)
    timeStart = driver.find_element_by_xpath('//*[@id="containerTimeStampUnix"]').text
    time.sleep(2)

print("Last timestamp " + driver.find_element_by_xpath('//*[@id="containerTimeStampUnix"]').text)
driver.quit()
sys.exit()
