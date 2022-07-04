# Learning to Blog
The Sentinel project entails so many different chapters that I finally learned how to use Github for blogging.

This post is organized in two parts:
1. The parts (almost) no one told me.
2. Links to some good information online.

<!-- The following produces a list of posts -->
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
**Trick #1**: Place blog post articles in a folder named ```_posts```. Write them in Markdown.

**Trick #2**: Define a ```baseurl``` in the ```_config.yml``` file, like this:

```baseurl: /ATtiny_Soil_Sentinel```

Variables you define in ```_config.yml``` become ```site``` variables in the page text.

**Trick #3**: Include a code block on every post page that lists the available blog articles. 

Mine looked something like this at the the time of writing:


<code><pre>
&lt;h2&gt; Articles in this Series&lt;/h2&gt;
&lt;ul&gt;
  {% for post in site.posts %}
    &lt;li&gt;
      &lt;h6&gt;
        &lt;a href="{{site.baseurl}}{{ post.url }}"
          {% if post.title == page.title %}
             style="color: black;"
          {% endif %}&gt;
          {* raw *}{{ post.date | date: "%Y-%m-%d" }} : {{ post.title }}{* endraw *}
        &lt;/a&gt;
        {* raw *}{% if post.title == page.title %}{* endraw *}
          &nbsp; &lt;&lt; You are here.
        {* raw *}{% endif %}{* endraw *}        
      &lt;/h6&gt;
    &lt;/li&gt;
  {* raw *}{% endfor %}{* endraw *}
&lt;/ul&gt;
</pre></code>


## Online references
The following links helped me to understand how Github does blogs.

<hr>

###### [Github Pages](https://pages.github.com/)
Remember that you can create files and folders directly in the Github web client, if you prefer.

It's interesting to me that Github says, &ldquo;You get one site per GitHub account and organization,
and unlimited project sites.&rdquo; Yet, they tell you only about building the "one" site for your account's user name.

<hr>

###### [Jekyll](https://jekyllrb.com/docs/step-by-step/01-setup/)
Here I've linked to the Step-by-Step Tutorial. The Jekyll site provides very nice navigation: lots of links on every page to other documentation and information.

<hr>

###### [Liquid](https://shopify.github.io/liquid/)
Liquid calls itself a Template Language. I would say it fills some of the same rolein flow control (if-then, case-when) and iteration (e.g., for loops) that PHP performs in a server-side blog application such as WordPress.

<hr>

###### [YAML](https://yaml.org/spec/1.2.2/)
This is one of those fun, recursive acronyms that open-source gurus dearly love. It supposedly means, &ldquo;YAML Ain't Markup Language&rdquo;. But what is it, then? YAML is a language for converting data between a text format easy for people to read and a compact data structure defined in a programming language.

Huh?

Jekyll and Liquid use YAML for the site configuration file and for page-specific variables.  YAML takes:

* name:value pairs that are easy and self-documenting to write as text, 
    * example: ```baseurl: /<repo_name```
* and transforms them into variables for Jekyll and Liquid to use,
    * example: {{ site.baseurl }}, which prints as ```/repo_name```.

<hr>

###### [SASS](https://sass-lang.com/)
It's a kind of souped-up CSS for styling web pages. Github uses it, so I include a reference to it. However, I believe that ordinary CSS works perfectly well also.

Note: Github will ignore any custom ```style``` tags or attributes you type directly into your page text. They have their reasons. Thankfully, they do allow you to create and use your own custom styling, if you wish. Follow Github's instructions for [Customizing your theme's CSS](https://docs.github.com/en/pages/setting-up-a-github-pages-site-with-jekyll/adding-a-theme-to-your-github-pages-site-using-jekyll#customizing-your-themes-css).

I link to this resource here for the sake of informational completeness. Editorial views expressed on their web site regarding topics other than technology are their own.

<hr>
###### [Markdown](https://docs.github.com/en/get-started/writing-on-github/getting-started-with-writing-and-formatting-on-github/basic-writing-and-formatting-syntax)
Github Pages transforms Markdown text into html. So you don't have to. Yay!
