const puppeteer = require('puppeteer-core');

(async () => {
    try {
        const browser = await puppeteer.launch({ executablePath: 'chromium-browser', headless: true, product: 'chrome' });
        const page = await browser.newPage();
        page.setDefaultNavigationTimeout(25 * 1000);
        await page.goto('https://www.google.com/');
        await page.screenshot({ path: 'screenshot.png' });

        await browser.close();
        console.log('screenshot taken');
    } catch (e) {
        console.log(e.message);
    }
})();
