"""Check that the WebAssembly game starts in a browser and reacts to clicks."""
import base64
import sys
import time

from playwright.sync_api import sync_playwright

URL = "http://localhost:8000/reversi.html"

# The same size as the iframe on the website
WIDTH = 420
HEIGHT = 480

with sync_playwright() as p:
    browser = p.chromium.launch(channel="chrome")
    page = browser.new_page(viewport={"width": WIDTH, "height": HEIGHT})
    errors = []
    page.on("pageerror", lambda e: errors.append(str(e)))
    page.goto(URL)
    time.sleep(10)
    before = page.screenshot()
    # Click all over the board: at least one click is a valid move
    for x in range(30, WIDTH, 50):
        for y in range(60, HEIGHT - 60, 50):
            page.mouse.click(x, y)
    time.sleep(1)
    after = page.screenshot()
    browser.close()

print("Screenshot:", base64.b64encode(after).decode())
if errors:
    sys.exit(f"Page errors: {errors}")
if before == after:
    sys.exit("Clicking did not change the page")
