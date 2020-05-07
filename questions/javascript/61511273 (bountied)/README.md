## JavaScript: On [Raspberry Pi Zero](https://www.raspberrypi.org/products/raspberry-pi-zer), [puppeteer](https://github.com/puppeteer/puppeteer) hangs after timeout exceeded

### Load a website on Headless Browser and take a snapshot

Link: https://stackoverflow.com/questions/61511273/

### Prerequisites

#### Dependencies

- Chromium Headless Browser
- NPM and NodeJS
- Puppeteer

##### Installation

```
$ sudo apt-get install chromium-browser chromium-codecs-ffmpeg --yes
$ npm init -Y
$ npm install puppeteer-core@1.11.0
```

#### Run

```
$ nodejs index.js
```

## Question

I'm having some issues getting my Raspberry Pi Zero to run `puppeteer` like I have seen it in this [tutorial](https://www.youtube.com/watch?v=6LnJ1zW5464&t=2s).

So far I have done something like:

```
$ sudo apt-get install chromium-browser chromium-codecs-ffmpeg --yes

$ npm init -Y
$ npm install puppeteer-core@1.11.0
```

also, tried without locking the core version to 1.11.0 - same results.

Here's my `index.js`:
```
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
```

And, when I run it like this I get timeout error:

```
$ node index.js
Navigation Timeout Exceeded: 25000ms exceeded
```

But, it just hangs. No exit!

Any help would be highly appreciated, thank you.

---

## Answer

Here are a few pointers that might be helpful for you:

You need to make sure that you have internet connectivity on your RPi that serves you well under 25 seconds timeout limit i.e. `page.setDefaultNavigationTimeout(25 * 1000);`. You can use `ping` command to observe the latency i.e. `ping google.com`.

I believe that you have an RPi Zero model with a 1GHz single-core processor and 512 MB RAM as mentioned [here][1]. So, the hardware and the OS would also be contributing factors here as opening a headless browser, taking a snapshot, storing it to a file; all these operations would take time. You can individually time these operations to have a better idea at a granular level about the total time spent.

I have tested it on a machine (Core i5 - 8 cores, 8 GB RAM with Ubuntu 18.04 LTS) and it took ~4 seconds. In that video tutorial, it took ~9 seconds.

So, a simple solution would be to use a longer timeout value.

Another thing that you can do is to host a simple static webpage on your local Apache Server and use its address (e.g. http://localhost:8080/index.html) to test it locally without the internet. The latency would be far less in this case and you'd be able to verify that it works on your RPi Zero. You might need to adjust timeout in this case too. You may use Python's [SimpleHTTPServer][2] as well instead of the Apache Server.

  [1]: https://www.raspberrypi.org/products/raspberry-pi-zero
  [2]: https://docs.python.org/2/library/simplehttpserver.html

---
