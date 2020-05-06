## HAProxy 1.5 - Serving static json file on 504 error

### `errorfile`: JSON Message on [HTTP 504 (Gateway Timeout)](https://httpstatuses.com/504)

Link: https://stackoverflow.com/questions/61485269/

## Question

I'm trying to set up HAProxy to server a static JSON file on 504 errors. To test, we've set up the configuration file to timeout after 10 seconds, and to use the `errorfile` option:

```
defaults
  log     global
  mode    http
  retries 3
  timeout client 10s
  timeout connect 10s
  timeout server 10s
  option tcplog
  balance  roundrobin

frontend https
  maxconn 2000
  bind 0.0.0.0:9000

  errorfile 504 /home/user1/test/error.json

  acl employee-api-service path_reg /employee/api.*
  use_backend servers-employee-api if employee-api-service

backend servers-employee-api
  server www.server.com 127.0.0.1:8000
```

Effectively, I'm trying to serve JSON instead of HTML on a timeout, so the backend service can fail gracefully. However, on testing, we could not get anything, neither HTML or JSON. On looking at the response, it simply says it failed, with no status code. Is my setup correct for `errorfile`?  Does HAProxy 1.5 support this?

---

## Answer

According to the documentation of [errorfile][1]:

```
<file>    designates a file containing the full HTTP response. It is
          recommended to follow the common practice of appending ".http" to
          the filename so that people do not confuse the response with HTML
          error pages, and to use absolute paths, since files are read
          before any chroot is performed.
```

So, the file should contain a **complete HTTP response** but you're trying to serve JSON only.

The documentation further says that:

```
For better HTTP compliance, it is
recommended that all header lines end with CR-LF and not LF alone.
```

The example configuration, for example, 

    errorfile 503 /etc/haproxy/errorfiles/503sorry.http

shows the common practice of `.http` extension for the error file.

You can find samples of some default error files [here][2].

Sample ([504.http][3]):

```
HTTP/1.0 504 Gateway Time-out
Cache-Control: no-cache
Connection: close
Content-Type: text/html

<html><body><h1>504 Gateway Time-out</h1>
The server didn't respond in time.
</body></html>

```

So, in your scenario, `504.http` would be like this:

```
HTTP/1.0 504 Gateway Time-out
Cache-Control: no-cache
Connection: close
Content-Type: application/json

{
    "message": "Gateway Timeout"
}

```

Also, you need to keep the file size under limit i.e. `BUFSIZE` (8 or 16 KB) as described in the documentation.

There might be some error logs for not serving your JSON file. You might want to look at HAProxy's logs again thoroughly. Just to be sure.

  [1]: https://cbonte.github.io/haproxy-dconv/configuration-1.5.html#4-errorfile
  [2]: https://github.com/joyent/haproxy-1.5/tree/master/examples/errorfiles
  [3]: https://github.com/joyent/haproxy-1.5/blob/master/examples/errorfiles/504.http

---
