# Learning to Blog
The Sentinel project entails so many different chapters that I finally learned how to use Github for blogging.

This post is organized in two parts:
1. The parts (almost) no one told me.
2. Links to some good information online.

{% include post_list.html %}

## The Parts No One Told Me
Including two sections:

<ul>
  <li><h4>Do It All in the Web Interface</h4></li>
  <li><h4>Three Key Tricks for Blogs in a Project Repository</h4></li>
</ul>

I feel safe in saying that all of the online tutorials and guides assume the user will create blog content on their own computer first.

You do not have to do it that way.

These guides teach how to download a bundle of software including Ruby, Jekyll, YAML and SASS. The tools transform text you write into web pages. Github deploys those tools on its servers. The tutorials expect that you will want the tools to be on your local machine, too. Maybe it's even a good idea. But it's not strictly necessary.

My practice is to build the repository first, including a descriptive README file. Sometimes I go farther to publish a web article about it after the code and examples are complete. Log in to Github, open the repo in the browser. The following sequence would work at the time of writing in early July, 2022:

* Create a branch named ```gh-pages``` and navigate to that branch.
* Click the Settings icon
* Click the Pages link in the Code and Automation group
* Under Source, choose the gh-pages branch and the /(root) folder. Click Save.
* Click Change Theme, choose a theme. For example, this page uses Slate.
* Navigate back to the ```gh-pages``` branch of the repo.

When a file named ```_config.yml``` shows up in the repository, it means the web page is being published.

What role does that file play?  It defines certain key:value pairs that affect how the web pages will look. You can add more definitions of your own. For example, I added the following:

```
title: ATtiny Soil Sensor
description: Much to learn!
```

You can see how those definitions are used the top of every page in this blog.

Behind the scenes, Jekyll transforms the README file into a home page. One does not have to write the html code for that page. Jekyll takes care of it.

Better yet, create a new home page file in the ```gh-pages``` branch. Write it in Markdown syntax. Name it "index.md". Jekyll will prefer to use that file as the home page, if it exists.

So far, so good, but how to add posts easily?

#### Three Key Tricks for Blogs in a Project Repository
**Trick #1**: Place blog post articles in a folder named ```_posts```.

**Trick #2**: Define a ```baseurl``` in the ```_config.yml``` file, like this:

```baseurl: /ATtiny_Soil_Sentinel```

**Trick #3**: Put a Jekyll list-builder code block on every page. Mine looks something like the following.





## Online references
