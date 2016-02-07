<?php
/**
 * @file
 * deninet_demo_blog.features.uuid_node.inc
 */

/**
 * Implements hook_uuid_features_default_content().
 */
function deninet_demo_blog_uuid_features_default_content() {
  $nodes = array();

  $nodes[] = array(
  'uid' => 1,
  'title' => 'Docker From Scratch, Part 2: Dockerfiles',
  'log' => '',
  'status' => 1,
  'comment' => 2,
  'promote' => 1,
  'sticky' => 0,
  'vuuid' => '2a157ba7-499b-4a7c-9b1f-0f91e7c27efc',
  'type' => 'blog',
  'language' => 'und',
  'created' => 1439349288,
  'tnid' => 0,
  'translate' => 0,
  'uuid' => '6a26fdae-cf25-4c3f-97d8-184487fed104',
  'revision_uid' => 1,
  'body' => array(
    'und' => array(
      0 => array(
        'value' => '<p><a href="/blog/1582/docker-scratch-part-1-installing-and-your-first-container">In the last post</a>, we pulled an ran a Docker container from the command line. Even though we only needed a few commands, it can become tedious to run the same lengthy command over and over each time we want to work with our container.</p>

<p>Worse, such repetition is prone to error. One thing we want from Docker is a <em>repeatable</em> environment: something that builds the same way each time we build it, on each system we build it on, for all the developers on our team. You might be tempted to just put everything in a script file, but even that has portability problems. Bash doesn’t work on Windows (without Cygwin). We need something that only depends on Docker itself.</p>

<h2>How to Make a Server with One Text File</h2>

<p>Docker includes the ability to build containers by using a <em>Dockerfile</em>. The Dockerfile is like a script, but only for creating a ready to use, Docker container. It instructs Docker which container on the Docker Hub to start with, what files to copy into the container, what commands to run while building the container, and what command to run when the container is ready to use.</p>

<p>Dockerfiles are weird. The syntax may look oddly archaic, but it is simple and straightforward enough to learn quickly. All Dockerfiles start with two lines:</p>

<pre>
FROM debian:wheezy
MAINTAINER your_email@example.com
</pre>

<p>The FROM statement instructs Docker what container on the Docker Hub this container will start with. Containers are a bit like that phrase, <a href="https://en.wikipedia.org/wiki/Turtles_all_the_way_down">“It’s turtles all the way down.”</a> All containers in existence are based on another container on the hub. It’s containers all the way down -- until you hit the mother of all containers, “scratch”. The “scratch” container is an empty *.tar.gz file. Even if you want to build your own container from an install disk, you’re still starting, quite literally, from scratch. In the above example we’re pulling from the “debian” container, but not just any Debian container, we’re specifically pulling from Debian 6, or “Wheezy”. There’s typically a special version keyword “latest” that refers to the newest version of that Linux distro. You separate the name of the container from the version with a full colon.</p>

<p>The MAINTAINER line simply specifies who built the Dockerfile. While the text that follows the maintainer can be anything, the common convention is an email address.</p>

<h2>Building the Container Using a Dockerfile</h2>

<p>The default name of a Dockerfile is just “Dockerfile”. No extension. It’s rather like a Vagrantfile in that respect, although Docker’s syntax is a bit more foolproof. To build your new container, you use the “build” docker command:</p>

<pre>
$ docker build .
Sending build context to Docker daemon 2.048 kB
Sending build context to Docker daemon 
Step 0 : FROM debian:wheezy
 ---&gt; 60c52dbe9d91
Step 1 : MAINTAINER your_email@example.com
 ---&gt; Running in 486f3a2255b4
 ---&gt; 64b0d7e8eef9
Removing intermediate container 486f3a2255b4
Successfully built 64b0d7e8eef9
</pre>

<p>The build command takes a single argument, the name of the hub repository to pull. In this case, we specified a single period, “.” to indicate the current directory. Docker will then look for a Dockerfile in the current working directory. Docker then starts building our image by pulling from the hub the container we specified in FROM. Then it reads the MAINTAINER line, and comes to the end of the file.</p>

<p>Once that’s built, you’ll probably want to run the “ps” command to see if it’s running. We’ll use the “-q” switch to only see the container IDs:</p>

<pre>
$ docker ps -q
$
</pre>

<p>Nothing! What the heck? Did the build command do anything at all? It did! Look back to the results of the “build” command. Notice the line “Removing intermediate container”? This hints at something else we need to learn about how Docker does things.</p>

<h2>Docker Images</h2>

<p>If you’ve worked with VMs, you know that the virtual hard drive is stored as a file or files on the host’s file system. At some point, you may have configured the system just as you wanted and wanted to preserve the state so you can fall back to it later. To do so, you created a “snapshot.” Version control systems like git also use a similar concept, where you create a snapshot of your source code as a commit which is identifiable by a unique hashcode.</p>

<p>Docker isn’t like a VM though, and doesn’t create a virtual hard drive like one. Instead, it works a lot more like a git repository. With each statement in the Dockerfile, Docker takes the current state of the container and commits it, generating an image. Like a git commit, Docker images are identified by a unique hashcode.</p>

<p>An image isn’t a running container: it’s more like a snapshot of a container that once was. We can list images using the “images” command:</p>

<pre>
$ docker images
REPOSITORY   TAG        IMAGE ID       CREATED           VIRTUAL SIZE
                        64b0d7e8eef9   1 minutes ago     85.02 MB
debian       wheezy     60c52dbe9d91   4 weeks ago       85.02 MB
debian       latest     9a61b6b1315e   4 weeks ago       125.2 MB
</pre>

<p>Wait, there are two debian images? Yes! There’s one from when we ran a Debian container interactively in the last post. Since we only specified “debian” it pulled the “debian:latest” repository. In our Dockerfile, we specified “debian:wheezy”, an earlier version of the OS. We also have one more image that has no repository and no version tag.</p>

<p>Look back to the output from the “build” command, paying close attention to the hashcodes. Then look at the output of the “images” command. After step 0 -- the FROM statement -- we see image ID starting with “60c”. Then the MAINTAINER step, we get a new container ID starting with “486”, and a new image ID starting with “64b”. A curious thing happened: the 486 container was removed! Why?</p>

<p>Remember, the Docker “build” command doesn’t build a running container, it only builds images. That’s why the so-called “intermediate” container was removed.</p>

<h2>Running an Image</h2>

<p>We can run a container from an image using the “run” command, just like before:</p>

<pre>
$ docker run -i -t 64b /bin/bash
</pre>

<p>Notice this time that instead of specifying the image name on the Docker Hub, we actually specify one we have locally. Even better, we only need to specify part of it. As long as it’s unique on the host, Docker will find it. Once inside, we can verify the Debian version:</p>

<pre>
root@71724ddf2f01:/# cat /etc/issue
Debian GNU/Linux 7 \\n \\l
</pre>

<p>We have Debian Wheezy, just like we expected. The trouble is, we have just a barebones container. What if we needed software like Apache or MySQL? Sure, we could run a script each time to add software to the container, but then we have the same problem again: shouldn’t the Dockerfile do this for us?</p>

<h2>Installing Software in a Dockerfile</h2>

<p>Dockerfiles can do more than specify FROM and MAINTAINER. Perhaps the most versatile command you can use in a Dockerfile is RUN.</p>

<p>The RUN statement does what it says on the tin: it runs a command on the container. We can use this statement to do all sorts of things in our container while building it, such as installing software.</p>

<pre>
FROM debian:wheezy
MAINTAINER your_email@example.com

RUN apt-get update
RUN apt-get install -y apache2
</pre>

<p>Here we’ve added two RUN statements. The first one updates the Debian software repositories. The second installs Apache. We can now create our container like we did before with the “build” command:</p>

<pre>
$ docker build .
Sending build context to Docker daemon 2.048 kB
Sending build context to Docker daemon 
Step 0 : FROM debian:wheezy
 ---&gt; 60c52dbe9d91
Step 1 : MAINTAINER your_email@example.com
 ---&gt; Using cache
 ---&gt; 64b0d7e8eef9
Step 2 : RUN apt-get update
 ---&gt; Running in 8652b461d629
Get:1 http://security.debian.org wheezy/updates Release.gpg [1554 B]
...
Fetched 8438 kB in 7s (1094 kB/s)
Reading package lists...
 ---&gt; eefa2fcb15e7
Removing intermediate container 8652b461d629
Step 3 : RUN apt-get install -y apache2
 ---&gt; Running in ef474ef3a976
Reading package lists...
Building dependency tree...
Reading state information...
…
Setting up libswitch-perl (2.16-2) ...
 ---&gt; aa084388ac30
Removing intermediate container ef474ef3a976
Successfully built aa084388ac30
</pre>

<p>Looking carefully at the command output, we can see that we get two new container IDs and two new image IDs:</p>

<pre>
$docker images
REPOSITORY   TAG        IMAGE ID       CREATED           VIRTUAL SIZE
                        aa084388ac30   2 minutes ago     145 MB
debian       wheezy     60c52dbe9d91   4 weeks ago       85.02 MB
debian       latest     9a61b6b1315e   4 weeks ago       125.2 MB
</pre>

<p>Now that’s interesting... Our old image ID is gone, replaced with the newest one, “aa0”. What happened? Docker images, like commits, stack on top of each other. It’s rather like how a git commit doesn’t have a complete copy of the source code at one point and time, but rather a list of changes to files. Each image is like a list of changes. This is one wonderful thing about Docker over VMs. Each time you update the container, you only record changes. This makes updating and saving changes in a container very, very fast and resource conservative.</p>

<h2>The Union FS and the Build Process</h2>

<p>This entire system of stacking images is based on an existing file system technology called a <a href="https://en.wikipedia.org/wiki/UnionFS">union file system</a>. It’s a method of mounting these lists of changes into a cohesive whole. The thing is, as you go back in the history of your container, you have to start from an initial image, or <em>base image</em>. The base image for our container is “debian:wheezy” on the Docker Hub.</p>

<p>Each statement in a Dockerfile results in a new image being taken. Even with two consecutive RUN statements, Docker will create a new image after each successful statement. This means that if any RUN statement (or any other statement in the Dockerfile) fails for whatever reason, Docker will automatically roll back to the last good image.</p>

<p>There’s also another implication that’s much more subtle. For each Dockerfile statement, Docker starts up a new container based on the last image. Docker then performs the statement on the container. For RUN commands, the command is run within the container. When the statement finishes successfully, Docker <em>shuts down</em> the container and takes a new image. That’s why we see “Running in…” and “Removing intermediate container…” pairs during our build command.</p>

<h2>Summary</h2>

<p>In this post, we’ve built a new Docker container using a repeatable and easy-to-understand Dockerfile. We learned about how Docker uses the UnionFS to store snapshots of containers as images. We’ve used the ADD statement to add software to our containers. Next time, we’ll expand our container to be easily runnable so we don’t to specify the command to run in the container.</p>

<a href="/blog/1585/docker-scratch-part-3-entrypoints-and-ports">Read Part 3</a>.',
        'summary' => '',
        'format' => 'full_html',
        'safe_value' => '<p><a href="/blog/1582/docker-scratch-part-1-installing-and-your-first-container">In the last post</a>, we pulled an ran a Docker container from the command line. Even though we only needed a few commands, it can become tedious to run the same lengthy command over and over each time we want to work with our container.</p>
<p>Worse, such repetition is prone to error. One thing we want from Docker is a <em>repeatable</em> environment: something that builds the same way each time we build it, on each system we build it on, for all the developers on our team. You might be tempted to just put everything in a script file, but even that has portability problems. Bash doesn’t work on Windows (without Cygwin). We need something that only depends on Docker itself.</p>
<h2>How to Make a Server with One Text File</h2>
<p>Docker includes the ability to build containers by using a <em>Dockerfile</em>. The Dockerfile is like a script, but only for creating a ready to use, Docker container. It instructs Docker which container on the Docker Hub to start with, what files to copy into the container, what commands to run while building the container, and what command to run when the container is ready to use.</p>
<p>Dockerfiles are weird. The syntax may look oddly archaic, but it is simple and straightforward enough to learn quickly. All Dockerfiles start with two lines:</p>
<pre>
FROM debian:wheezy
MAINTAINER your_email@example.com
</pre><p>The FROM statement instructs Docker what container on the Docker Hub this container will start with. Containers are a bit like that phrase, <a href="https://en.wikipedia.org/wiki/Turtles_all_the_way_down">“It’s turtles all the way down.”</a> All containers in existence are based on another container on the hub. It’s containers all the way down -- until you hit the mother of all containers, “scratch”. The “scratch” container is an empty *.tar.gz file. Even if you want to build your own container from an install disk, you’re still starting, quite literally, from scratch. In the above example we’re pulling from the “debian” container, but not just any Debian container, we’re specifically pulling from Debian 6, or “Wheezy”. There’s typically a special version keyword “latest” that refers to the newest version of that Linux distro. You separate the name of the container from the version with a full colon.</p>
<p>The MAINTAINER line simply specifies who built the Dockerfile. While the text that follows the maintainer can be anything, the common convention is an email address.</p>
<h2>Building the Container Using a Dockerfile</h2>
<p>The default name of a Dockerfile is just “Dockerfile”. No extension. It’s rather like a Vagrantfile in that respect, although Docker’s syntax is a bit more foolproof. To build your new container, you use the “build” docker command:</p>
<pre>
$ docker build .
Sending build context to Docker daemon 2.048 kB
Sending build context to Docker daemon 
Step 0 : FROM debian:wheezy
 ---&gt; 60c52dbe9d91
Step 1 : MAINTAINER your_email@example.com
 ---&gt; Running in 486f3a2255b4
 ---&gt; 64b0d7e8eef9
Removing intermediate container 486f3a2255b4
Successfully built 64b0d7e8eef9
</pre><p>The build command takes a single argument, the name of the hub repository to pull. In this case, we specified a single period, “.” to indicate the current directory. Docker will then look for a Dockerfile in the current working directory. Docker then starts building our image by pulling from the hub the container we specified in FROM. Then it reads the MAINTAINER line, and comes to the end of the file.</p>
<p>Once that’s built, you’ll probably want to run the “ps” command to see if it’s running. We’ll use the “-q” switch to only see the container IDs:</p>
<pre>
$ docker ps -q
$
</pre><p>Nothing! What the heck? Did the build command do anything at all? It did! Look back to the results of the “build” command. Notice the line “Removing intermediate container”? This hints at something else we need to learn about how Docker does things.</p>
<h2>Docker Images</h2>
<p>If you’ve worked with VMs, you know that the virtual hard drive is stored as a file or files on the host’s file system. At some point, you may have configured the system just as you wanted and wanted to preserve the state so you can fall back to it later. To do so, you created a “snapshot.” Version control systems like git also use a similar concept, where you create a snapshot of your source code as a commit which is identifiable by a unique hashcode.</p>
<p>Docker isn’t like a VM though, and doesn’t create a virtual hard drive like one. Instead, it works a lot more like a git repository. With each statement in the Dockerfile, Docker takes the current state of the container and commits it, generating an image. Like a git commit, Docker images are identified by a unique hashcode.</p>
<p>An image isn’t a running container: it’s more like a snapshot of a container that once was. We can list images using the “images” command:</p>
<pre>
$ docker images
REPOSITORY   TAG        IMAGE ID       CREATED           VIRTUAL SIZE
                        64b0d7e8eef9   1 minutes ago     85.02 MB
debian       wheezy     60c52dbe9d91   4 weeks ago       85.02 MB
debian       latest     9a61b6b1315e   4 weeks ago       125.2 MB
</pre><p>Wait, there are two debian images? Yes! There’s one from when we ran a Debian container interactively in the last post. Since we only specified “debian” it pulled the “debian:latest” repository. In our Dockerfile, we specified “debian:wheezy”, an earlier version of the OS. We also have one more image that has no repository and no version tag.</p>
<p>Look back to the output from the “build” command, paying close attention to the hashcodes. Then look at the output of the “images” command. After step 0 -- the FROM statement -- we see image ID starting with “60c”. Then the MAINTAINER step, we get a new container ID starting with “486”, and a new image ID starting with “64b”. A curious thing happened: the 486 container was removed! Why?</p>
<p>Remember, the Docker “build” command doesn’t build a running container, it only builds images. That’s why the so-called “intermediate” container was removed.</p>
<h2>Running an Image</h2>
<p>We can run a container from an image using the “run” command, just like before:</p>
<pre>
$ docker run -i -t 64b /bin/bash
</pre><p>Notice this time that instead of specifying the image name on the Docker Hub, we actually specify one we have locally. Even better, we only need to specify part of it. As long as it’s unique on the host, Docker will find it. Once inside, we can verify the Debian version:</p>
<pre>
root@71724ddf2f01:/# cat /etc/issue
Debian GNU/Linux 7 \\n \\l
</pre><p>We have Debian Wheezy, just like we expected. The trouble is, we have just a barebones container. What if we needed software like Apache or MySQL? Sure, we could run a script each time to add software to the container, but then we have the same problem again: shouldn’t the Dockerfile do this for us?</p>
<h2>Installing Software in a Dockerfile</h2>
<p>Dockerfiles can do more than specify FROM and MAINTAINER. Perhaps the most versatile command you can use in a Dockerfile is RUN.</p>
<p>The RUN statement does what it says on the tin: it runs a command on the container. We can use this statement to do all sorts of things in our container while building it, such as installing software.</p>
<pre>
FROM debian:wheezy
MAINTAINER your_email@example.com

RUN apt-get update
RUN apt-get install -y apache2
</pre><p>Here we’ve added two RUN statements. The first one updates the Debian software repositories. The second installs Apache. We can now create our container like we did before with the “build” command:</p>
<pre>
$ docker build .
Sending build context to Docker daemon 2.048 kB
Sending build context to Docker daemon 
Step 0 : FROM debian:wheezy
 ---&gt; 60c52dbe9d91
Step 1 : MAINTAINER your_email@example.com
 ---&gt; Using cache
 ---&gt; 64b0d7e8eef9
Step 2 : RUN apt-get update
 ---&gt; Running in 8652b461d629
Get:1 http://security.debian.org wheezy/updates Release.gpg [1554 B]
...
Fetched 8438 kB in 7s (1094 kB/s)
Reading package lists...
 ---&gt; eefa2fcb15e7
Removing intermediate container 8652b461d629
Step 3 : RUN apt-get install -y apache2
 ---&gt; Running in ef474ef3a976
Reading package lists...
Building dependency tree...
Reading state information...
…
Setting up libswitch-perl (2.16-2) ...
 ---&gt; aa084388ac30
Removing intermediate container ef474ef3a976
Successfully built aa084388ac30
</pre><p>Looking carefully at the command output, we can see that we get two new container IDs and two new image IDs:</p>
<pre>
$docker images
REPOSITORY   TAG        IMAGE ID       CREATED           VIRTUAL SIZE
                        aa084388ac30   2 minutes ago     145 MB
debian       wheezy     60c52dbe9d91   4 weeks ago       85.02 MB
debian       latest     9a61b6b1315e   4 weeks ago       125.2 MB
</pre><p>Now that’s interesting... Our old image ID is gone, replaced with the newest one, “aa0”. What happened? Docker images, like commits, stack on top of each other. It’s rather like how a git commit doesn’t have a complete copy of the source code at one point and time, but rather a list of changes to files. Each image is like a list of changes. This is one wonderful thing about Docker over VMs. Each time you update the container, you only record changes. This makes updating and saving changes in a container very, very fast and resource conservative.</p>
<h2>The Union FS and the Build Process</h2>
<p>This entire system of stacking images is based on an existing file system technology called a <a href="https://en.wikipedia.org/wiki/UnionFS">union file system</a>. It’s a method of mounting these lists of changes into a cohesive whole. The thing is, as you go back in the history of your container, you have to start from an initial image, or <em>base image</em>. The base image for our container is “debian:wheezy” on the Docker Hub.</p>
<p>Each statement in a Dockerfile results in a new image being taken. Even with two consecutive RUN statements, Docker will create a new image after each successful statement. This means that if any RUN statement (or any other statement in the Dockerfile) fails for whatever reason, Docker will automatically roll back to the last good image.</p>
<p>There’s also another implication that’s much more subtle. For each Dockerfile statement, Docker starts up a new container based on the last image. Docker then performs the statement on the container. For RUN commands, the command is run within the container. When the statement finishes successfully, Docker <em>shuts down</em> the container and takes a new image. That’s why we see “Running in…” and “Removing intermediate container…” pairs during our build command.</p>
<h2>Summary</h2>
<p>In this post, we’ve built a new Docker container using a repeatable and easy-to-understand Dockerfile. We learned about how Docker uses the UnionFS to store snapshots of containers as images. We’ve used the ADD statement to add software to our containers. Next time, we’ll expand our container to be easily runnable so we don’t to specify the command to run in the container.</p>
<p><a href="/blog/1585/docker-scratch-part-3-entrypoints-and-ports">Read Part 3</a>.</p>
',
        'safe_summary' => '',
      ),
    ),
  ),
  'field_blog_image' => array(),
  'field_topic' => array(
    'und' => array(
      0 => array(
        'tid' => 1,
        'uuid' => '51e9afd5-0b71-46fb-8471-0aa7bad81c10',
      ),
    ),
  ),
  'path' => array(
    'pathauto' => 1,
  ),
  'cid' => 0,
  'last_comment_name' => NULL,
  'last_comment_uid' => 1,
  'comment_count' => 0,
  'flag_friend_access' => FALSE,
  'name' => 'admin',
  'picture' => 0,
  'data' => 'b:0;',
  'pathauto_perform_alias' => FALSE,
  'date' => '2015-08-12 03:14:48 +0000',
);
  $nodes[] = array(
  'uid' => 1,
  'title' => 'Docker from Scratch, Part 4: Compose and Volumes',
  'log' => '',
  'status' => 1,
  'comment' => 2,
  'promote' => 1,
  'sticky' => 0,
  'vuuid' => '32d8a550-1a3e-4861-b0a2-efd55bb68cc1',
  'type' => 'blog',
  'language' => 'und',
  'created' => 1441163002,
  'tnid' => 0,
  'translate' => 0,
  'uuid' => '8eec3ff5-ceb2-427d-832b-38c6a89f9b91',
  'revision_uid' => 1,
  'body' => array(
    'und' => array(
      0 => array(
        'value' => '<p><a href="/blog/1585/docker-scratch-part-3-entrypoints-and-ports">In the last post</a>, we’ve created a repeatable web server container using a single file, the Dockerfile. While this is great, there’s one big limitation to a Dockerfile: It can only create one container. Docker containers are also only intended to run one process. What do we do if we want to run a web server, and a database, and a Solr instance, and a…</p>
<p>We’d need to create a Dockerfile for each server process. Given that we’d need to call the Docker “run” command for each container, building and starting containers would get rather tedious. Thankfully, we don’t need to do this thanks to an additional utility, Docker Compose</p>
<h2>Installing Compose</h2>
<p>Docker Compose -- or, just “Compose” -- is typically installed with Docker on Mac OS X and Windows systems. On Linux systems, Compose is typically available as a separate package. Check the <a href="https://docs.docker.com/installation/">installation page</a> on the Compose documentation site for details.</p>
<p>Compose wasn’t originally a part of Docker, but rather a completely separate project called <a href="http://www.fig.sh/">Docker Fig</a>. You may still find references for Fig out on the Internet. Thankfully, the idea behind Fig and file formats are mostly (if not completely) identical to Compose.</p>
<h2>The Compose File</h2>
<p>Just like Docker has a Dockerfile, Compose also has it’s own file, docker-compose.yml. There are several big differences between the Compose file and the Dockerfile. First of all, the Compose file is descriptive, rather than instructive. Dockerfiles tend to be made mostly of statements that are executed to build a container. The Compose file describes the container in its running state, leaving the details on how to build the container to Dockerfiles.</p>
<p>The Compose file is also based on an existing file format, <a href="https://en.wikipedia.org/wiki/YAML">YAML</a>. YAML is often used to describe hierarchical structures while being light, and human readable. Think about it like XML without the “closing tag tax”.</p>
<p>A simple Compose file for our web server container would look like this:</p>
<code><pre>
web:
   build: .
</pre></code>
<p>The Compose file would be saved as docker-compose.yml in the same directory as our Dockerfile. The first line defines a <em>service</em>, basically a container. Every statement under that describes the container. In YAML, indentation is significant, like it is in Python.</p>
</p>
<p>Typically, you see one of two statements immediately following the service name in a Compose file: a “build” statement, or an “image” statement. Both are analogous to the FROM statement in the Dockerfile, with an important difference. The “build” statement is always a path to a Dockerfile on the local system. The “image” statement always refers to an image on the Docker Hub.</p>
<h2>Overriding Statements</h2>
<p>When building services in Compose, there are times you might want to change some of the defaults that are specified in the Dockerfile. If you’re using the “build” statement, it’s pretty easy to just modify the Dockerfile you have locally. What about when using “image” and you’re referring to a remote image on the Hub? It turns out, you can easily override many things in your Compose file.</p>
<p>For our Apache Web Server container, we may wish to specify a different port than that in the Dockerfile. In fact, you can do more than that:</p>
</p>
<code><pre>
web:
   build: .
   ports:
      - “80:80”
</pre></code>
<p>The “ports” statement takes a list of network ports to open between the host system and the container. Each pair is on a separate line, preceded by a hyphen -- the normal YAML list format. The pair first specifies the port as seen by the host system, with the port after the full colon is the port the container expects. This makes it very easy to start our Apache container on a non-default port such as 8080. We only need to change the “ports” statement in the Compose file.</p>
<p>YAML has a bit of a quirk where numbers lower than 60 are concerned. YAML may try to parse those as base-60 rather than base-10. For this reason, we specify the port pair as a string by enclosing it in double quotes.</p>
<p>The “ports” statement isn’t the only thing we can override in the Dockerfile. There are “command” and “entrypoint” statements that correspond to “CMD” and “ENTRYPOINT” in the Dockerfile. You can find a complete list on the <a href="https://docs.docker.com/compose/yml/">Docker Compose Reference</a> site.</p>
<h2>Managing Containers with Compose</h2>
<p>Using Compose instead of basic Dockerfiles also has a small but much needed advantage. Until now, whenever we ran, killed, or removed a container, we had to specify the container ID. We were always looking up these IDs using the docker “ps” command. This can be both tedious and error prone; we wouldn’t want to kill or destroy the wrong container on a production server!</p>
<p>Starting a container with Compose is pretty similar to when you used the Docker “run” command. Instead of “run”, however, you use “up”:</p>
<code><pre>
$ docker-compose up -d
</pre></code>
<p>Similar to the Vagrant “up” command, the Compose “up” command builds the containers specified by docker-compose.yml, and then runs them. The “-d” switch runs the containers in the background. That’s right, container<strong><em>s</em></strong>. You can actually build multiple related containers in just one Compose file!</p>
<p>Stopping and destroying all the containers described in the Compose file is even easier:</p>
<code><pre>
$ docker-compose kill
$ docker-compose rm
</pre></code>
<p>The “kill” command will stop all the containers in our Compose file, while “rm” will remove and delete them. Notice we didn’t need to specify the container IDs at all. Yay! But how did it do this? Well, if you run the Docker “ps” command after “up”ing your services, you’ll notice something interesting:</p>
<code><pre>
$ docker ps
CONTAINER ID   COMMAND                STATUS       NAMES
245fbb0bf255   "apachectl -D FOREGR   Up 18 secs   dockerthingy_web_1 

$ pwd
/home/tess/dockerthingy
</pre></code>
<p>Ah-ha! Compose created the container with a special name. It used the parent directory of the docker-compose.yml file, and then appended the service name with an instance number. This way, Compose can always identify the containers to stop or destroy.</p>
</p>
<p>This format also carries with it another advantage. Typically, the docker-compose.yml file is placed in the root directory of your project or git repository. This not only makes it easier to “up” your development environment, the directory will tend to have a more unique name to avoid potential conflicts on the same Docker host.</p>
</p>
<h2>Getting Files into the Container</h2>
<p>So far we’ve been concerned with just building our container and getting it into a usable state; and there’s been a lot to learn! Now, however, we can start putting our container to use. For a web server container, we want to get our application files into the server docroot so that Apache may serve them.</p>
<p>Dockerfiles support a COPY statement that will -- you guessed it -- copy the specified file from the host system into the container:</p>
<code><pre>
COPY path/on/host.txt /target/path/on/container.txt
</pre></code>
<p>There’s also an ADD command that builds upon COPY in two key ways: ADD can take a remote URL as a source path and download the file over the Internet. ADD may also take an archive file in *.tar.gz or *.zip format and extract its contents in the destination directory. While this sounds great, it’s best practice to always use COPY if you are copying a local file into the container.</p>
<p>Now that we know how to get files into the container, let’s update our Dockerfile to copy an HTML file into our container’s web docroot:</p>
<code><pre>
FROM debian:wheezy
MAINTAINER your_email@example.com

RUN apt-get update
RUN apt-get install -y apache2

COPY index.html /var/www

CMD ["-D", "FOREGROUND"]
ENTRYPOINT ["apachectl"]
</pre></code>
<p>We’ve added the COPY statement immediately before the CMD and ENTRYPOINT statements. Even though this is a simple change, we need to rebuild our container. Normally, we’d do this with the Docker “build” command. There’s also a “build” command for Compose. This will force the contains to be rebuilt:</p>
<code><pre>
$ docker-compose build
</pre></code>
<p>Now we can up the Compose service again. This time, when look at the container’s webserver port, we should see our updated index file.</p>
<code><pre>
$ docker-compose up -d

$ curl docker.dev
&lt;html&gt;
&lt;body&gt;
&lt;h1&gt;Behold, my amazing page!&lt;/h1&gt;
&lt;p&gt;Okay, yeah, it sucks. Sorry.&lt;/p&gt;
&lt;/body&gt;
&lt;/html&gt;
</pre></code>
<h2>Volumes</h2>
<p>The problem with both COPY and ADD is that it only works during the build phase, not the run phase. If we ever need to change the web files we’re developing, we’d have to stop the container, destroy it, and build it again. While that process is much faster with Docker than it is with a VM, we’d rather just work on the same files as in our project directory, and have them updated in the container whenever we save changes on the host’s filesystem.</p>
<p>The solution is <em>volumes</em>. Volumes allow us to mount a directory on our local system as a directory in the container. We can do this with the “volumes” statement in our Compose file:</p>
<code><pre>
web:
   build: .
   ports:
      - “80:80”
   volumes:
      - docroot:/var/www
</pre></code>
<p>Like “ports”, “volumes” is a YAML list that takes host:container pairings. Instead of ports, we specify the path to the directory on the host system, with the path to the directory to mount inside the container. It can take both relative and absolute paths. Typically, you use a relative path for the host system and an absolute path for the container.</p>
<p>For our example Compose file, we’ve created a “docroot” directory within our project directory. We can then add our application files -- including index.html -- to it:</p>
</p>
<code><pre>
dockerthingy/
├── docker-compose.yml
├── Dockerfile
└── docroot/
    └── index.html
</pre></code>
<p><strong>Make sure to remove the COPY from our Dockerfile!</strong> We won’t need it any longer since we’re using volumes. When we “up” the container, Docker will mount our docroot/ directory in the container at the Apache Web Server default document root, /var/www. If we make any changes to our index.html file, they will be synced to the container automatically.</p>
</p>
<h2>Summary</h2>
<p>Compose is an awesome addition to Docker. It allows you to define multiple containers as a whole. We’ve used COPY and ADD to get custom files into the container from the host OS. Then, we used volumes to sync a directory on our host’s filesystem to the container. Next time, we’ll add a second container to Compose file for running a database.</p>
<p><a href="/blog/1588/docker-scratch-part-5-custom-entrypoints-and-configuration">Read Part 5</a>.</p>',
        'summary' => '',
        'format' => 'full_html',
        'safe_value' => '<p><a href="/blog/1585/docker-scratch-part-3-entrypoints-and-ports">In the last post</a>, we’ve created a repeatable web server container using a single file, the Dockerfile. While this is great, there’s one big limitation to a Dockerfile: It can only create one container. Docker containers are also only intended to run one process. What do we do if we want to run a web server, and a database, and a Solr instance, and a…</p>
<p>We’d need to create a Dockerfile for each server process. Given that we’d need to call the Docker “run” command for each container, building and starting containers would get rather tedious. Thankfully, we don’t need to do this thanks to an additional utility, Docker Compose</p>
<h2>Installing Compose</h2>
<p>Docker Compose -- or, just “Compose” -- is typically installed with Docker on Mac OS X and Windows systems. On Linux systems, Compose is typically available as a separate package. Check the <a href="https://docs.docker.com/installation/">installation page</a> on the Compose documentation site for details.</p>
<p>Compose wasn’t originally a part of Docker, but rather a completely separate project called <a href="http://www.fig.sh/">Docker Fig</a>. You may still find references for Fig out on the Internet. Thankfully, the idea behind Fig and file formats are mostly (if not completely) identical to Compose.</p>
<h2>The Compose File</h2>
<p>Just like Docker has a Dockerfile, Compose also has it’s own file, docker-compose.yml. There are several big differences between the Compose file and the Dockerfile. First of all, the Compose file is descriptive, rather than instructive. Dockerfiles tend to be made mostly of statements that are executed to build a container. The Compose file describes the container in its running state, leaving the details on how to build the container to Dockerfiles.</p>
<p>The Compose file is also based on an existing file format, <a href="https://en.wikipedia.org/wiki/YAML">YAML</a>. YAML is often used to describe hierarchical structures while being light, and human readable. Think about it like XML without the “closing tag tax”.</p>
<p>A simple Compose file for our web server container would look like this:</p>
<p><code></code></p>
<pre>
web:
   build: .
</pre><p></p>
<p>The Compose file would be saved as docker-compose.yml in the same directory as our Dockerfile. The first line defines a <em>service</em>, basically a container. Every statement under that describes the container. In YAML, indentation is significant, like it is in Python.</p>

<p>Typically, you see one of two statements immediately following the service name in a Compose file: a “build” statement, or an “image” statement. Both are analogous to the FROM statement in the Dockerfile, with an important difference. The “build” statement is always a path to a Dockerfile on the local system. The “image” statement always refers to an image on the Docker Hub.</p>
<h2>Overriding Statements</h2>
<p>When building services in Compose, there are times you might want to change some of the defaults that are specified in the Dockerfile. If you’re using the “build” statement, it’s pretty easy to just modify the Dockerfile you have locally. What about when using “image” and you’re referring to a remote image on the Hub? It turns out, you can easily override many things in your Compose file.</p>
<p>For our Apache Web Server container, we may wish to specify a different port than that in the Dockerfile. In fact, you can do more than that:</p>

<p><code></code></p>
<pre>
web:
   build: .
   ports:
      - “80:80”
</pre><p></p>
<p>The “ports” statement takes a list of network ports to open between the host system and the container. Each pair is on a separate line, preceded by a hyphen -- the normal YAML list format. The pair first specifies the port as seen by the host system, with the port after the full colon is the port the container expects. This makes it very easy to start our Apache container on a non-default port such as 8080. We only need to change the “ports” statement in the Compose file.</p>
<p>YAML has a bit of a quirk where numbers lower than 60 are concerned. YAML may try to parse those as base-60 rather than base-10. For this reason, we specify the port pair as a string by enclosing it in double quotes.</p>
<p>The “ports” statement isn’t the only thing we can override in the Dockerfile. There are “command” and “entrypoint” statements that correspond to “CMD” and “ENTRYPOINT” in the Dockerfile. You can find a complete list on the <a href="https://docs.docker.com/compose/yml/">Docker Compose Reference</a> site.</p>
<h2>Managing Containers with Compose</h2>
<p>Using Compose instead of basic Dockerfiles also has a small but much needed advantage. Until now, whenever we ran, killed, or removed a container, we had to specify the container ID. We were always looking up these IDs using the docker “ps” command. This can be both tedious and error prone; we wouldn’t want to kill or destroy the wrong container on a production server!</p>
<p>Starting a container with Compose is pretty similar to when you used the Docker “run” command. Instead of “run”, however, you use “up”:</p>
<p><code></code></p>
<pre>
$ docker-compose up -d
</pre><p></p>
<p>Similar to the Vagrant “up” command, the Compose “up” command builds the containers specified by docker-compose.yml, and then runs them. The “-d” switch runs the containers in the background. That’s right, container<strong><em>s</em></strong>. You can actually build multiple related containers in just one Compose file!</p>
<p>Stopping and destroying all the containers described in the Compose file is even easier:</p>
<p><code></code></p>
<pre>
$ docker-compose kill
$ docker-compose rm
</pre><p></p>
<p>The “kill” command will stop all the containers in our Compose file, while “rm” will remove and delete them. Notice we didn’t need to specify the container IDs at all. Yay! But how did it do this? Well, if you run the Docker “ps” command after “up”ing your services, you’ll notice something interesting:</p>
<p><code></code></p>
<pre>
$ docker ps
CONTAINER ID   COMMAND                STATUS       NAMES
245fbb0bf255   "apachectl -D FOREGR   Up 18 secs   dockerthingy_web_1 

$ pwd
/home/tess/dockerthingy
</pre><p></p>
<p>Ah-ha! Compose created the container with a special name. It used the parent directory of the docker-compose.yml file, and then appended the service name with an instance number. This way, Compose can always identify the containers to stop or destroy.</p>

<p>This format also carries with it another advantage. Typically, the docker-compose.yml file is placed in the root directory of your project or git repository. This not only makes it easier to “up” your development environment, the directory will tend to have a more unique name to avoid potential conflicts on the same Docker host.</p>

<h2>Getting Files into the Container</h2>
<p>So far we’ve been concerned with just building our container and getting it into a usable state; and there’s been a lot to learn! Now, however, we can start putting our container to use. For a web server container, we want to get our application files into the server docroot so that Apache may serve them.</p>
<p>Dockerfiles support a COPY statement that will -- you guessed it -- copy the specified file from the host system into the container:</p>
<p><code></code></p>
<pre>
COPY path/on/host.txt /target/path/on/container.txt
</pre><p></p>
<p>There’s also an ADD command that builds upon COPY in two key ways: ADD can take a remote URL as a source path and download the file over the Internet. ADD may also take an archive file in *.tar.gz or *.zip format and extract its contents in the destination directory. While this sounds great, it’s best practice to always use COPY if you are copying a local file into the container.</p>
<p>Now that we know how to get files into the container, let’s update our Dockerfile to copy an HTML file into our container’s web docroot:</p>
<p><code></code></p>
<pre>
FROM debian:wheezy
MAINTAINER your_email@example.com

RUN apt-get update
RUN apt-get install -y apache2

COPY index.html /var/www

CMD ["-D", "FOREGROUND"]
ENTRYPOINT ["apachectl"]
</pre><p></p>
<p>We’ve added the COPY statement immediately before the CMD and ENTRYPOINT statements. Even though this is a simple change, we need to rebuild our container. Normally, we’d do this with the Docker “build” command. There’s also a “build” command for Compose. This will force the contains to be rebuilt:</p>
<p><code></code></p>
<pre>
$ docker-compose build
</pre><p></p>
<p>Now we can up the Compose service again. This time, when look at the container’s webserver port, we should see our updated index file.</p>
<p><code></code></p>
<pre>
$ docker-compose up -d

$ curl docker.dev
&lt;html&gt;
&lt;body&gt;
&lt;h1&gt;Behold, my amazing page!&lt;/h1&gt;
&lt;p&gt;Okay, yeah, it sucks. Sorry.&lt;/p&gt;
&lt;/body&gt;
&lt;/html&gt;
</pre><p></p>
<h2>Volumes</h2>
<p>The problem with both COPY and ADD is that it only works during the build phase, not the run phase. If we ever need to change the web files we’re developing, we’d have to stop the container, destroy it, and build it again. While that process is much faster with Docker than it is with a VM, we’d rather just work on the same files as in our project directory, and have them updated in the container whenever we save changes on the host’s filesystem.</p>
<p>The solution is <em>volumes</em>. Volumes allow us to mount a directory on our local system as a directory in the container. We can do this with the “volumes” statement in our Compose file:</p>
<p><code></code></p>
<pre>
web:
   build: .
   ports:
      - “80:80”
   volumes:
      - docroot:/var/www
</pre><p></p>
<p>Like “ports”, “volumes” is a YAML list that takes host:container pairings. Instead of ports, we specify the path to the directory on the host system, with the path to the directory to mount inside the container. It can take both relative and absolute paths. Typically, you use a relative path for the host system and an absolute path for the container.</p>
<p>For our example Compose file, we’ve created a “docroot” directory within our project directory. We can then add our application files -- including index.html -- to it:</p>

<p><code></code></p>
<pre>
dockerthingy/
├── docker-compose.yml
├── Dockerfile
└── docroot/
    └── index.html
</pre><p></p>
<p><strong>Make sure to remove the COPY from our Dockerfile!</strong> We won’t need it any longer since we’re using volumes. When we “up” the container, Docker will mount our docroot/ directory in the container at the Apache Web Server default document root, /var/www. If we make any changes to our index.html file, they will be synced to the container automatically.</p>

<h2>Summary</h2>
<p>Compose is an awesome addition to Docker. It allows you to define multiple containers as a whole. We’ve used COPY and ADD to get custom files into the container from the host OS. Then, we used volumes to sync a directory on our host’s filesystem to the container. Next time, we’ll add a second container to Compose file for running a database.</p>
<p><a href="/blog/1588/docker-scratch-part-5-custom-entrypoints-and-configuration">Read Part 5</a>.</p>
',
        'safe_summary' => '',
      ),
    ),
  ),
  'field_blog_image' => array(),
  'field_topic' => array(
    'und' => array(
      0 => array(
        'tid' => 1,
        'uuid' => '51e9afd5-0b71-46fb-8471-0aa7bad81c10',
      ),
    ),
  ),
  'path' => array(
    'pathauto' => 1,
  ),
  'cid' => 0,
  'last_comment_name' => NULL,
  'last_comment_uid' => 1,
  'comment_count' => 0,
  'flag_friend_access' => FALSE,
  'name' => 'admin',
  'picture' => 0,
  'data' => 'b:0;',
  'pathauto_perform_alias' => FALSE,
  'date' => '2015-09-02 03:03:22 +0000',
);
  $nodes[] = array(
  'uid' => 1,
  'title' => 'Docker from Scratch, Part 1: Installing and your First Container',
  'log' => '',
  'status' => 1,
  'comment' => 2,
  'promote' => 1,
  'sticky' => 0,
  'vuuid' => '37af1860-142b-451e-80bc-0e46d1f95f0d',
  'type' => 'blog',
  'language' => 'und',
  'created' => 1438962153,
  'tnid' => 0,
  'translate' => 0,
  'uuid' => 'dbc52bf8-0138-49f5-93ba-0c84339cb415',
  'revision_uid' => 1,
  'body' => array(
    'und' => array(
      0 => array(
        'value' => '<p>The last few months I’ve been engaged in a quest to understand something new to me. Since the mid-2000s, I’ve been using virtualization technologies to run classroom environments, test software, and run local web servers for development. First, it was using VMware Player, then Server, and today everything I virtualize runs on the open source Virtualbox. So when I heard about <em>containerization</em>, I was stunned.</p>

<p>“How can you start tens of virtualized instances in only seconds? It’s unreal!” And yet, the demos didn’t lie. I wanted to dig in myself, but having discovered Vagrant, I wanted to wait until there was a similar ecosystem for containers. Today, there’s no excuse; Docker is ready.</p>

<p>I’d been using Docker at work for months now, but how it worked and how you build your own remained a mystery to me. Unlike virtualization, there’s more than one key concept to learn. So one day, I just decided to sit down and dig in.</p>

<h2><strong>Installing Docker</strong></h2>

<p>Docker is easiest to install on a machine running Linux. There are fewer dependencies, and it’s really Docker’s native environment. Consult your distro’s documentation on how to install Docker.</p>

<p>Now if you are using Docker on Mac or Windows, you’re <em>not</em> out of luck! You can still run Docker, but the installation process is a bit more complicated and involves several steps. First, <a href="https://www.virtualbox.org">download and install Virtualbox</a>. Then, go to <a href="https://www.docker.com/">https://www.docker.com/</a> and click “Get Started”. Their documentation is well written, and will get you set up.</p>

<p>Once that’s done, we’re ready to start running containers.</p>

<h2><strong>Running Your First Container</strong></h2>

<p>There are many containers ready to download and run online. Instead of hunting for them and installing them yourself, Docker assumes you have an Internet connection and maintains a listing of containers for use -- the <a href="https://registry.hub.docker.com/">Docker Registry</a>. To download one of these pre-made containers for use, you issue a “pull” command. It’s rather like pulling an repository from github.</p>

<pre><code>
$ docker pull debian</code></pre>

<p>You might notice docker pulling what looks like multiple commits for the same container. Once the image has been pulled, then we can start up with the “run” command.</p>

<pre><code>
$ docker run -i -t debian /bin/bash</code></pre>

<p>If everything goes well, you’ll be dropped into a bash shell. Huzzah! You’ve just run your first container. Now go ahead and poke around. One thing that’s particularly interesting is to list the contents of the root directory. When you do, you’ll notice that it looks very much like a basic Debian installation. There’s a typical Linux directory structure, and many utilities are available just as you’d expect.</p>

<p>This isn’t much different from any time you installed and run a Linux VM. It downloaded and started up faster than a normal VM, and it’s actually taking up less memory and disk space on your system. WHAT IS THIS MAGIC!?</p>

<p>First, let’s break down that docker command a bit. “run” instructs docker to run a container. The “-i” means run interactively. We don’t <em>need </em>to run a container interactively, and often we won’t. The “-t” is actually related to the “-i”: it instructs docker to emulate a terminal. You can run the command without the “-t”, but it would look a little strange. The next part, “debian” is the container we want to run. In this case, we’re running the Debian container we pulled earlier. The last bit’s the command we want to run in the container.</p>

<h2><strong>Listing Containers</strong></h2>

<p>Go ahead and exit the interactive session like you would any command line application: use Control-C or enter “exit”. Once you’re certain your back to your host OS, let’s take a look at all of our running Docker containers by issuing the “docker ps” command.</p>

<pre><code>
$ docker ps
CONTAINER ID       IMAGE        COMMAND            CREATED             STATUS
</code></pre>

<p>Wait, “ps”? Like the list processes command on Linux? Yeah, but with Docker it only lists running containers. That’s kind of a weird thing to call it, but we’ll explain that later. You may notice the output of the command is empty. The hell? Isn’t our container still running like any VM would? The answer is no. Let’s list all our containers, running or stopped, by using the “-a” switch on the “ps” command:</p>

<pre><code>
$ docker ps -a
CONTAINER ID       IMAGE        COMMAND            CREATED             STATUS                     
0c6142a4488a       debian       "/bin/bash"        8 seconds ago       Exited
<code></pre>

<p><em>There’s</em> our container! But why did it stop? If you’ve used VMs before, you’re used to the idea that they work just like Linux running on physical hardware. You need to boot them up and shut them down. Containers aren’t like that. In fact, containers are a subtly different beast entirely from VMs.</p>

<h2><strong>“A Container Is Just a Process”</strong></h2>

<p>I’ve heard this before from others trying to explain to me just what in the heck a container is. To say a container is “just a process” only mystifies it further. Yet it gets at the key reason why containers are so much faster than VMs.</p>

<p>Containers aren’t VMs. When you run a VM, you are essentially emulating all the physical hardware necessary for the guest OS to run. The guest OS itself has its own kernel, background processes, and services necessary to make a functional Linux environment. This requires a lot of overhead to run, and makes VMs memory-, disk-, and CPU-intensive. Containers, on the other hand, don’t run an operating system.</p>

<p>When we ran our first container, we specified what to run in the container -- /bin/bash, or the Bash shell. This was the <em>only</em> thing running in that container. There’s no additional Linux kernel, no background processes, no services. Just the one process we need. Containers are better thought of not as VMs, but applications.</p>

<p>A container runs a single Linux process. While the container doesn’t have a kernel of its own, it does have all the files, libraries, and utilities necessary for the process to run. It’s like we took all the OS out of Linux, and made it into a specially boxed and packaged runtime. This is why the container stopped when we quit the shell. The container is still in its own little world, in a way, but without the virtual hardware or OS baggage to slow things down. This is also why when we listed the root directory, it looked very much like a full Linux OS. All the files are there to support the Linux <em>userland</em>, but none of the kernel.</p>

<h2><strong>Summary</strong></h2>

<p>So far we’ve installed Docker, and started our first container. We learned that containers only run a single Linux process, rather than an entire OS. Next time, we’ll start building a repeatable docker container by writing a <em>DockerFile</em>.</p>

<a href="/blog/1583/docker-scratch-part-2-dockerfiles">Read Part 2</a>.',
        'summary' => '',
        'format' => 'full_html',
        'safe_value' => '<p>The last few months I’ve been engaged in a quest to understand something new to me. Since the mid-2000s, I’ve been using virtualization technologies to run classroom environments, test software, and run local web servers for development. First, it was using VMware Player, then Server, and today everything I virtualize runs on the open source Virtualbox. So when I heard about <em>containerization</em>, I was stunned.</p>
<p>“How can you start tens of virtualized instances in only seconds? It’s unreal!” And yet, the demos didn’t lie. I wanted to dig in myself, but having discovered Vagrant, I wanted to wait until there was a similar ecosystem for containers. Today, there’s no excuse; Docker is ready.</p>
<p>I’d been using Docker at work for months now, but how it worked and how you build your own remained a mystery to me. Unlike virtualization, there’s more than one key concept to learn. So one day, I just decided to sit down and dig in.</p>
<h2><strong>Installing Docker</strong></h2>
<p>Docker is easiest to install on a machine running Linux. There are fewer dependencies, and it’s really Docker’s native environment. Consult your distro’s documentation on how to install Docker.</p>
<p>Now if you are using Docker on Mac or Windows, you’re <em>not</em> out of luck! You can still run Docker, but the installation process is a bit more complicated and involves several steps. First, <a href="https://www.virtualbox.org">download and install Virtualbox</a>. Then, go to <a href="https://www.docker.com/">https://www.docker.com/</a> and click “Get Started”. Their documentation is well written, and will get you set up.</p>
<p>Once that’s done, we’re ready to start running containers.</p>
<h2><strong>Running Your First Container</strong></h2>
<p>There are many containers ready to download and run online. Instead of hunting for them and installing them yourself, Docker assumes you have an Internet connection and maintains a listing of containers for use -- the <a href="https://registry.hub.docker.com/">Docker Registry</a>. To download one of these pre-made containers for use, you issue a “pull” command. It’s rather like pulling an repository from github.</p>
<pre><code>
$ docker pull debian</code></pre><p>You might notice docker pulling what looks like multiple commits for the same container. Once the image has been pulled, then we can start up with the “run” command.</p>
<pre><code>
$ docker run -i -t debian /bin/bash</code></pre><p>If everything goes well, you’ll be dropped into a bash shell. Huzzah! You’ve just run your first container. Now go ahead and poke around. One thing that’s particularly interesting is to list the contents of the root directory. When you do, you’ll notice that it looks very much like a basic Debian installation. There’s a typical Linux directory structure, and many utilities are available just as you’d expect.</p>
<p>This isn’t much different from any time you installed and run a Linux VM. It downloaded and started up faster than a normal VM, and it’s actually taking up less memory and disk space on your system. WHAT IS THIS MAGIC!?</p>
<p>First, let’s break down that docker command a bit. “run” instructs docker to run a container. The “-i” means run interactively. We don’t <em>need </em>to run a container interactively, and often we won’t. The “-t” is actually related to the “-i”: it instructs docker to emulate a terminal. You can run the command without the “-t”, but it would look a little strange. The next part, “debian” is the container we want to run. In this case, we’re running the Debian container we pulled earlier. The last bit’s the command we want to run in the container.</p>
<h2><strong>Listing Containers</strong></h2>
<p>Go ahead and exit the interactive session like you would any command line application: use Control-C or enter “exit”. Once you’re certain your back to your host OS, let’s take a look at all of our running Docker containers by issuing the “docker ps” command.</p>
<pre><code>
$ docker ps
CONTAINER ID       IMAGE        COMMAND            CREATED             STATUS
</code></pre><p>Wait, “ps”? Like the list processes command on Linux? Yeah, but with Docker it only lists running containers. That’s kind of a weird thing to call it, but we’ll explain that later. You may notice the output of the command is empty. The hell? Isn’t our container still running like any VM would? The answer is no. Let’s list all our containers, running or stopped, by using the “-a” switch on the “ps” command:</p>
<pre><code>
$ docker ps -a
CONTAINER ID       IMAGE        COMMAND            CREATED             STATUS                     
0c6142a4488a       debian       "/bin/bash"        8 seconds ago       Exited
<code></code></code></pre><p><em>There’s</em> our container! But why did it stop? If you’ve used VMs before, you’re used to the idea that they work just like Linux running on physical hardware. You need to boot them up and shut them down. Containers aren’t like that. In fact, containers are a subtly different beast entirely from VMs.</p>
<h2><strong>“A Container Is Just a Process”</strong></h2>
<p>I’ve heard this before from others trying to explain to me just what in the heck a container is. To say a container is “just a process” only mystifies it further. Yet it gets at the key reason why containers are so much faster than VMs.</p>
<p>Containers aren’t VMs. When you run a VM, you are essentially emulating all the physical hardware necessary for the guest OS to run. The guest OS itself has its own kernel, background processes, and services necessary to make a functional Linux environment. This requires a lot of overhead to run, and makes VMs memory-, disk-, and CPU-intensive. Containers, on the other hand, don’t run an operating system.</p>
<p>When we ran our first container, we specified what to run in the container -- /bin/bash, or the Bash shell. This was the <em>only</em> thing running in that container. There’s no additional Linux kernel, no background processes, no services. Just the one process we need. Containers are better thought of not as VMs, but applications.</p>
<p>A container runs a single Linux process. While the container doesn’t have a kernel of its own, it does have all the files, libraries, and utilities necessary for the process to run. It’s like we took all the OS out of Linux, and made it into a specially boxed and packaged runtime. This is why the container stopped when we quit the shell. The container is still in its own little world, in a way, but without the virtual hardware or OS baggage to slow things down. This is also why when we listed the root directory, it looked very much like a full Linux OS. All the files are there to support the Linux <em>userland</em>, but none of the kernel.</p>
<h2><strong>Summary</strong></h2>
<p>So far we’ve installed Docker, and started our first container. We learned that containers only run a single Linux process, rather than an entire OS. Next time, we’ll start building a repeatable docker container by writing a <em>DockerFile</em>.</p>
<p><a href="/blog/1583/docker-scratch-part-2-dockerfiles">Read Part 2</a>.</p>
',
        'safe_summary' => '',
      ),
    ),
  ),
  'field_blog_image' => array(),
  'field_topic' => array(
    'und' => array(
      0 => array(
        'tid' => 1,
        'uuid' => '51e9afd5-0b71-46fb-8471-0aa7bad81c10',
      ),
    ),
  ),
  'path' => array(
    'pathauto' => 1,
  ),
  'cid' => 0,
  'last_comment_name' => NULL,
  'last_comment_uid' => 1,
  'comment_count' => 0,
  'flag_friend_access' => FALSE,
  'name' => 'admin',
  'picture' => 0,
  'data' => 'b:0;',
  'pathauto_perform_alias' => FALSE,
  'date' => '2015-08-07 15:42:33 +0000',
);
  $nodes[] = array(
  'uid' => 1,
  'title' => 'Docker From Scratch, Part 5: Custom Entrypoints and Configuration',
  'log' => '',
  'status' => 1,
  'comment' => 2,
  'promote' => 1,
  'sticky' => 0,
  'vuuid' => '13368498-726c-47fa-84b0-74d7014420b3',
  'type' => 'blog',
  'language' => 'und',
  'created' => 1441329794,
  'tnid' => 0,
  'translate' => 0,
  'uuid' => 'ecd1a212-e887-449d-a9b7-a7b778e88184',
  'revision_uid' => 1,
  'body' => array(
    'und' => array(
      0 => array(
        'value' => '<p><a href="/blog/1587/docker-scratch-part-4-compose-and-volumes">In the last post</a>, we introduced Docker Compose. Now, instead of looking up image IDs, managing our containers requires only a few easy to remember commands. We also used volumes to sync a directory on the host OS to the container for easier development.</p>
<p>The wonderful thing about Docker Compose is that it can manage more than one container at a time. We can create multiple containers and manage them all as if they were part of the same, cohesive whole. In this post, we’re going to expand our containers to include a Database server and set up remote access.</p>
<h2>Organizing our Project</h2>
<p>Before we can start on any of that, however, we need to think about reorganizing our project. Right now our project directory looks like this:</p>
<code><pre>
/home/tess/dockerthingy
├── docker-compose.yml
├── Dockerfile
└── docroot
    └── index.html
</pre></code>
<p>Notice the Dockerfile is in our project root. That was fine when we only had one container, but now that we’re adding another we have two options. In our Compose file we had the following statement:</p>
<code><pre>
web:
   build: .
</pre></code>
<p>This instructed Compose to look for a Dockerfile in the same directory as the docker-compose.yml file. If we were to add another, we’d have to rename our Dockerfiles and clearly identify which is for what container. The problem is, this is nonstandard; Docker expects the file to be called “Dockerfile”. A better way is to put each Dockerfile in a separate directory so we don’t have to give it a non-standard name:</p>
<code><pre>
/home/tess/dockerthingy
├── .docker
│   ├── db
│   └── web
│       └── Dockerfile
├── docker-compose.yml
└── docroot
    └── index.html
</pre></code>
<p>Our new .docker/ directory houses all of the files necessary to support our containers with the exception of the Compose file. You may or may not wish to mark the directory as hidden by prefacing the name with a period. I tend to hide the directory in my project because I rarely need to update the container configuration. After all, the focus is on building my application, not maintaining containers! This is particularly true when using pre-made images on the Docker Hub rather than our own Dockerfiles. We keep the docker-compose.yml file in the root directory so that we may easily “up” and “kill” the containers without descending into the .docker/ directory.</p>
<h2>Building our Database Container</h2>
<p>With our new project organization, we can start creating our new database container. While there are a lot of DBs out there to choose from, for this project I’ll use MySQL. Installing MySQL from the command line isn’t difficult, but we need to conduct an <em>unattended</em> installation. MySQL tends to ask for a root password during installation from the command line. We need to find a way around that.</p>
<p>We start our database Dockerfile the same way as we did for the web server Dockerfile, with a FROM and a MAINTAINER:</p>
<code><pre>
FROM debian:wheezy
MAINTAINER your_email@example.com
</pre></code>
<p>Then, we follow by updating the software repository and then installing MySQL server. We combine both commands into a single RUN statement using the double-ampersand operator (&amp;&amp;). We also break the statement across two lines for readability using a backslash (\\). We use a single RUN statement to prevent Docker from creating an intermediate image between updating the repo, and installing the database.</p>
<code><pre>
RUN apt-get update && \\
    apt-get -yq install mysql-server
</pre></code>
<p>We also use the “-q” or “quiet” switch of the “apt-get” command when installing the database server. When installing MySQL from the command line, you are required to enter the root password. Without the -q switch, the installation process would halt, and our container build would hang. Of course by using the “-q” switch, this means we’re installing the database with <em>no</em> root password. This is fine since we’re only using the container for development, not production.</p>
<p>Continuing in the Dockerfile, we also want to EXPOSE the MySQL port so we can access the database server remotely:</p>
<code><pre>
EXPOSE 3306
</pre></code>
<p>And we want to set an ENTRYPOINT to the MySQL executable:</p>
<code><pre>
ENTRYPOINT ["/usr/bin/mysqld_safe"]
</pre></code>
<h2>Updating our Compose File</h2>
<p>With our new project organization and our database Dockerfile, we need to update our docker-compose.yml file. First, we’ll update the <em>web</em> service to use the location or our new Dockerfile in the “build” statement. Then, we’ll add a new <em>db</em> service:</p>
<code><pre>
web:
   build: .docker/web
   ports:
      - "80:80"
   volumes:
      - docroot:/var/www
db:
   build: .docker/db
   ports:
      - 3306:3306
</pre></code>
<p>No real surprises in our updated Compose file: we map the MySQL default port of 3306 to both the host OS and the container. Now that we’ve made these changes, we can rebuild the container:</p>
<code><pre>
$ docker-compose build
$ docker-compose up -d
</pre></code>
<h2>Setting up Remote Access</h2>
<p>At this point it looks like we have a running, perfectly usable database container. But when we try to connect to the container, we run into a problem:</p>
<code><pre>
$ mysql -u root -h 127.0.0.1 -P 3306
ERROR 1045 (28000): Access denied for user \'root\'@\'172.17.42.1\' (using password: NO)
</pre></code>
<p>No, that <em>is</em> the correct login. The problem is that by default, MySQL will not allow remote access, only local access. If we were working on VM instead of a container, we could SSH in and work with the database. In a container, however, there’s no way to SSH in. After all, the only process running in the container is the database server.</p>
<p>To set up remote access, we need to do two things. We need to configure the MySQL server to accept incoming connections from any IP address. Normally, this is a <em>very bad idea,</em> but we’re only using this container for development, not production. Secondly, we need to create a database, and a user for that database. To do this, we update our Dockerfile:</p>
<code><pre>
FROM debian:wheezy
MAINTAINER your_email@example.com

RUN apt-get update && \\
    apt-get -yq install mysql-server

RUN sed -i -e "s/^bind-address\\s*=\\s*127.0.0.1/bind-address = 0.0.0.0/" /etc/mysql/my.cnf

COPY run.sh /tmp/mysql_run.sh
RUN chmod +x /tmp/mysql_run.sh

EXPOSE 3306

ENTRYPOINT ["/tmp/mysql_run.sh"]
</pre></code>
<p>The first thing you may notice is the new RUN statement that executes the <a href="https://en.wikipedia.org/wiki/Sed">"sed” command</a>. This is done after installing the database server, and edits the “bind-address” parameter of the MySQL configuration file, my.cnf. This updates the configuration in place to allow incoming network connections from any address. We could replace the my.cnf file entirely using a COPY statement. Since we’re only changing one parameter, however, editing it in place makes more sense.</p>
<p>The next thing you may notice is that we’ve completely <em>replaced</em> the ENTRYPOINT! In the Dockerfile, we COPYed a new script into the container, mysql_run.sh. We used a RUN statement to make it executable, and then set the ENTRYPOINT to it.</p>
<h2>Custom Entrypoints</h2>
<p>There’s nothing preventing us from creating custom ENTRYPOINTs in Docker. Often there are key advantages in wrapping our target executable in a script. As we’ll see later, one of the advantages is that it allows us to execute something in the run-phase, not the build-phase.</p>
<p>So what’s inside our custom entrypoint?</p>
<code><pre>
#!/usr/bin/env bash

set -m
set -e

mysqld_safe &

sleep 10

mysql -u root -e "CREATE DATABASE IF NOT EXISTS your_db"
mysql -u root -e "GRANT ALL ON your_db.* to \'your_user\'@\'%\' IDENTIFIED BY \'your_password\'"
mysql -u root -e "FLUSH PRIVILEGES"

fg
</pre></code>
<p>The script is straightforward. After the hashbang, we configure the bash shell environment in two key ways: “set -m” forces <em>job control</em> to be on, even in a scripting environment. We’ll need this later in the script. “set -e” instructs the shell to terminate the script at the first failure of any set in the script. This is <strong>very</strong> useful for scripts that run non-interactively as it doesn’t leave the container in a half set-up state.</p>
<p>Next, we start up the MySQL server process, mysql_safe. Instead of running it in the foreground, however, we run it in the background. We do this so the script retains control and allows us to run additional commands after the server starts up. Next, we wait 10 seconds before continuing. This isn’t a best practice approach; there are ways of pinging the MySQL process for readiness that shave off vital seconds.The downside is the scripting is more complicated. Using the “sleep” command to wait 10 seconds will suffice for our needs.</p>
<p>Then, we run three queries against the database server. First, we create a new database, “your_db”. Then, we create a new user, “your_user”, grant them unfettered access to “your_db”, and set the password of “your_password”. Notice that when we created the user, we identified their host as ‘%’, or, any address. This is also a really bad idea for a production server, but perfectly fine for a development one. Finally, we flush the privileges.</p>
<p>The final command, “fg” looks trivial, but it’s also the most important line in the script. It brings the MySQL server process that we backgrounded earlier into the foreground. That way, control is passed back to “mysql_safe”, where it will stay for as long as the container is running.</p>
<p>Now we can re-”build” and up the container:</p>
<code><pre>
$ docker-compose build
$ docker-compose up -d
</pre></code>
<p>This time, when we connect to the database, we can use our new user account:</p>
<code><pre>
$ mysql -u your_user --password=your_password -h docker.dev -P 3306
Welcome to the MariaDB monitor.  Commands end with ; or \\g.
Your MySQL connection id is 6
Server version: 5.5.44-0+deb7u1 (Debian)

Copyright (c) 2000, 2015, Oracle, MariaDB Corporation Ab and others.

Type \'help;\' or \'\\h\' for help. Type \'\\c\' to clear the current input statement.

MySQL [(none)]> show databases;
+--------------------+
| Database           |
+--------------------+
| information_schema |
| your_db            |
+--------------------+
</pre></code>
<p>Beautiful!</p>
<h2>Passing Customizations in Compose</h2>
<p>This is all great, but we obviously don’t want a database called “your_db”, or a user called “your_user”. While we could change the Dockerfile to use the configurations we want, this misses the point.</p>
<p>In most Compose files, we are <em>not</em> referencing local Dockerfiles. Instead of “build”, we use the “image” statement and refer to a Docker image on the Hub. That way, we can reuse the work others have already put in. This also creates a problem: How do we pass customizations to 3rd party containers? Compose provides a subtle but powerful way to do this using the “environment” statement.</p>
<p>Both Dockerfiles and Compose files may specify environment variables to set in the container. You can use this to pass configuration details such as the database name, username, and password... but there’s a catch. The ENV statement in the Dockerfile sets environment variables during the build phase. These values persist into the run-phase of the container. Compose’s “environment” statement, on the other hand, may only set environment variables during the run phase. This means we can only use environment variables set in docker-compose.yml in a Dockerfile’s ENTRYPOINT, not in RUN statements.</p>
<p>Thankfully, we already replaced the ENTRYPOINT with a custom script. This makes things <em>much</em> easier for us! First, let’s update our docker-compose.yml with the environment variables we want to pass:</p>
<code><pre>
web:
   build: .docker/web
   ports:
      - "80:80"
   volumes:
      - docroot:/var/www
db:
   build: .docker/db
   ports:
      - 3306:3306
   environment:
      - MYSQL_DB=drupal8
      - MYSQL_USER=drupal
      - MYSQL_PASS=thisisawesome
</pre></code>
<p>The “environment” statement takes a list of one or more environment variables to pass to the container in <code>NAME_OF_VARIABLE=value_of_variable</code> format. Next, we need to update our ENTRYPOINT script, “mysql_run.sh”:</p>
<code><pre>
#!/usr/bin/env bash

set -m
set -e

MYSQL_DB=${MYSQL_DB:-your_db}
MYSQL_USER=${MYSQL_USER:-your_user}
MYSQL_PASS=${MYSQL_PASS:-your_password}

mysqld_safe &

sleep 10

mysql -u root -e "CREATE DATABASE IF NOT EXISTS ${MYSQL_DB}"
mysql -u root -e "GRANT ALL ON ${MYSQL_DB}.* to \'${MYSQL_USER}\'@\'%\' IDENTIFIED BY \'${MYSQL_PASS}\'"
mysql -u root -e "FLUSH PRIVILEGES"

fg
</pre></code>
<p>You’ll notice that we inline the variables in our queries to the server that create the database and user. We also add some basic input protection. For each variable that we use, we define a default:</p>
<code><pre>
MYSQL_DB=${MYSQL_DB:-your_db}
</pre></code>
<p>This way, if there’s a typo in the Compose file, or an environment value is not set, the script falls back to the default. Now when we rebuild and up the containers, we get our custom database, user and password without having the modify the Dockerfile.</p>
<code><pre>
$ mysql -u drupal --password=thisisawesome -h docker.dev -P 3306   
Welcome to the MariaDB monitor.  Commands end with ; or \\g.
Your MySQL connection id is 6
Server version: 5.5.44-0+deb7u1 (Debian)

Copyright (c) 2000, 2015, Oracle, MariaDB Corporation Ab and others.

Type \'help;\' or \'\\h\' for help. Type \'\\c\' to clear the current input statement.

MySQL [(none)]> show databases;
+--------------------+
| Database           |
+--------------------+
| information_schema |
| drupal8            |
+--------------------+
2 rows in set (0.00 sec)
</pre></code>
<h2>Summary</h2>
<p>We’ve expanded our Docker development environment a lot. We’ve not only added a new database container, but also created a custom ENTRYPOINT and added custom configuration in our Compose file. We’ve laid the foundation for an awesome, lightweight, and repeatable development environment. Next time, we’ll start to link together our containers and get our custom application code running.</p>
',
        'summary' => '',
        'format' => 'full_html',
        'safe_value' => '<p><a href="/blog/1587/docker-scratch-part-4-compose-and-volumes">In the last post</a>, we introduced Docker Compose. Now, instead of looking up image IDs, managing our containers requires only a few easy to remember commands. We also used volumes to sync a directory on the host OS to the container for easier development.</p>
<p>The wonderful thing about Docker Compose is that it can manage more than one container at a time. We can create multiple containers and manage them all as if they were part of the same, cohesive whole. In this post, we’re going to expand our containers to include a Database server and set up remote access.</p>
<h2>Organizing our Project</h2>
<p>Before we can start on any of that, however, we need to think about reorganizing our project. Right now our project directory looks like this:</p>
<p><code></code></p>
<pre>
/home/tess/dockerthingy
├── docker-compose.yml
├── Dockerfile
└── docroot
    └── index.html
</pre><p></p>
<p>Notice the Dockerfile is in our project root. That was fine when we only had one container, but now that we’re adding another we have two options. In our Compose file we had the following statement:</p>
<p><code></code></p>
<pre>
web:
   build: .
</pre><p></p>
<p>This instructed Compose to look for a Dockerfile in the same directory as the docker-compose.yml file. If we were to add another, we’d have to rename our Dockerfiles and clearly identify which is for what container. The problem is, this is nonstandard; Docker expects the file to be called “Dockerfile”. A better way is to put each Dockerfile in a separate directory so we don’t have to give it a non-standard name:</p>
<p><code></code></p>
<pre>
/home/tess/dockerthingy
├── .docker
│   ├── db
│   └── web
│       └── Dockerfile
├── docker-compose.yml
└── docroot
    └── index.html
</pre><p></p>
<p>Our new .docker/ directory houses all of the files necessary to support our containers with the exception of the Compose file. You may or may not wish to mark the directory as hidden by prefacing the name with a period. I tend to hide the directory in my project because I rarely need to update the container configuration. After all, the focus is on building my application, not maintaining containers! This is particularly true when using pre-made images on the Docker Hub rather than our own Dockerfiles. We keep the docker-compose.yml file in the root directory so that we may easily “up” and “kill” the containers without descending into the .docker/ directory.</p>
<h2>Building our Database Container</h2>
<p>With our new project organization, we can start creating our new database container. While there are a lot of DBs out there to choose from, for this project I’ll use MySQL. Installing MySQL from the command line isn’t difficult, but we need to conduct an <em>unattended</em> installation. MySQL tends to ask for a root password during installation from the command line. We need to find a way around that.</p>
<p>We start our database Dockerfile the same way as we did for the web server Dockerfile, with a FROM and a MAINTAINER:</p>
<p><code></code></p>
<pre>
FROM debian:wheezy
MAINTAINER your_email@example.com
</pre><p></p>
<p>Then, we follow by updating the software repository and then installing MySQL server. We combine both commands into a single RUN statement using the double-ampersand operator (&amp;&amp;). We also break the statement across two lines for readability using a backslash (\\). We use a single RUN statement to prevent Docker from creating an intermediate image between updating the repo, and installing the database.</p>
<p><code></code></p>
<pre>
RUN apt-get update &amp;&amp; \\
    apt-get -yq install mysql-server
</pre><p></p>
<p>We also use the “-q” or “quiet” switch of the “apt-get” command when installing the database server. When installing MySQL from the command line, you are required to enter the root password. Without the -q switch, the installation process would halt, and our container build would hang. Of course by using the “-q” switch, this means we’re installing the database with <em>no</em> root password. This is fine since we’re only using the container for development, not production.</p>
<p>Continuing in the Dockerfile, we also want to EXPOSE the MySQL port so we can access the database server remotely:</p>
<p><code></code></p>
<pre>
EXPOSE 3306
</pre><p></p>
<p>And we want to set an ENTRYPOINT to the MySQL executable:</p>
<p><code></code></p>
<pre>
ENTRYPOINT ["/usr/bin/mysqld_safe"]
</pre><p></p>
<h2>Updating our Compose File</h2>
<p>With our new project organization and our database Dockerfile, we need to update our docker-compose.yml file. First, we’ll update the <em>web</em> service to use the location or our new Dockerfile in the “build” statement. Then, we’ll add a new <em>db</em> service:</p>
<p><code></code></p>
<pre>
web:
   build: .docker/web
   ports:
      - "80:80"
   volumes:
      - docroot:/var/www
db:
   build: .docker/db
   ports:
      - 3306:3306
</pre><p></p>
<p>No real surprises in our updated Compose file: we map the MySQL default port of 3306 to both the host OS and the container. Now that we’ve made these changes, we can rebuild the container:</p>
<p><code></code></p>
<pre>
$ docker-compose build
$ docker-compose up -d
</pre><p></p>
<h2>Setting up Remote Access</h2>
<p>At this point it looks like we have a running, perfectly usable database container. But when we try to connect to the container, we run into a problem:</p>
<p><code></code></p>
<pre>
$ mysql -u root -h 127.0.0.1 -P 3306
ERROR 1045 (28000): Access denied for user \'root\'@\'172.17.42.1\' (using password: NO)
</pre><p></p>
<p>No, that <em>is</em> the correct login. The problem is that by default, MySQL will not allow remote access, only local access. If we were working on VM instead of a container, we could SSH in and work with the database. In a container, however, there’s no way to SSH in. After all, the only process running in the container is the database server.</p>
<p>To set up remote access, we need to do two things. We need to configure the MySQL server to accept incoming connections from any IP address. Normally, this is a <em>very bad idea,</em> but we’re only using this container for development, not production. Secondly, we need to create a database, and a user for that database. To do this, we update our Dockerfile:</p>
<p><code></code></p>
<pre>
FROM debian:wheezy
MAINTAINER your_email@example.com

RUN apt-get update &amp;&amp; \\
    apt-get -yq install mysql-server

RUN sed -i -e "s/^bind-address\\s*=\\s*127.0.0.1/bind-address = 0.0.0.0/" /etc/mysql/my.cnf

COPY run.sh /tmp/mysql_run.sh
RUN chmod +x /tmp/mysql_run.sh

EXPOSE 3306

ENTRYPOINT ["/tmp/mysql_run.sh"]
</pre><p></p>
<p>The first thing you may notice is the new RUN statement that executes the <a href="https://en.wikipedia.org/wiki/Sed">"sed” command</a>. This is done after installing the database server, and edits the “bind-address” parameter of the MySQL configuration file, my.cnf. This updates the configuration in place to allow incoming network connections from any address. We could replace the my.cnf file entirely using a COPY statement. Since we’re only changing one parameter, however, editing it in place makes more sense.</p>
<p>The next thing you may notice is that we’ve completely <em>replaced</em> the ENTRYPOINT! In the Dockerfile, we COPYed a new script into the container, mysql_run.sh. We used a RUN statement to make it executable, and then set the ENTRYPOINT to it.</p>
<h2>Custom Entrypoints</h2>
<p>There’s nothing preventing us from creating custom ENTRYPOINTs in Docker. Often there are key advantages in wrapping our target executable in a script. As we’ll see later, one of the advantages is that it allows us to execute something in the run-phase, not the build-phase.</p>
<p>So what’s inside our custom entrypoint?</p>
<p><code></code></p>
<pre>
#!/usr/bin/env bash

set -m
set -e

mysqld_safe &amp;

sleep 10

mysql -u root -e "CREATE DATABASE IF NOT EXISTS your_db"
mysql -u root -e "GRANT ALL ON your_db.* to \'your_user\'@\'%\' IDENTIFIED BY \'your_password\'"
mysql -u root -e "FLUSH PRIVILEGES"

fg
</pre><p></p>
<p>The script is straightforward. After the hashbang, we configure the bash shell environment in two key ways: “set -m” forces <em>job control</em> to be on, even in a scripting environment. We’ll need this later in the script. “set -e” instructs the shell to terminate the script at the first failure of any set in the script. This is <strong>very</strong> useful for scripts that run non-interactively as it doesn’t leave the container in a half set-up state.</p>
<p>Next, we start up the MySQL server process, mysql_safe. Instead of running it in the foreground, however, we run it in the background. We do this so the script retains control and allows us to run additional commands after the server starts up. Next, we wait 10 seconds before continuing. This isn’t a best practice approach; there are ways of pinging the MySQL process for readiness that shave off vital seconds.The downside is the scripting is more complicated. Using the “sleep” command to wait 10 seconds will suffice for our needs.</p>
<p>Then, we run three queries against the database server. First, we create a new database, “your_db”. Then, we create a new user, “your_user”, grant them unfettered access to “your_db”, and set the password of “your_password”. Notice that when we created the user, we identified their host as ‘%’, or, any address. This is also a really bad idea for a production server, but perfectly fine for a development one. Finally, we flush the privileges.</p>
<p>The final command, “fg” looks trivial, but it’s also the most important line in the script. It brings the MySQL server process that we backgrounded earlier into the foreground. That way, control is passed back to “mysql_safe”, where it will stay for as long as the container is running.</p>
<p>Now we can re-”build” and up the container:</p>
<p><code></code></p>
<pre>
$ docker-compose build
$ docker-compose up -d
</pre><p></p>
<p>This time, when we connect to the database, we can use our new user account:</p>
<p><code></code></p>
<pre>
$ mysql -u your_user --password=your_password -h docker.dev -P 3306
Welcome to the MariaDB monitor.  Commands end with ; or \\g.
Your MySQL connection id is 6
Server version: 5.5.44-0+deb7u1 (Debian)

Copyright (c) 2000, 2015, Oracle, MariaDB Corporation Ab and others.

Type \'help;\' or \'\\h\' for help. Type \'\\c\' to clear the current input statement.

MySQL [(none)]&gt; show databases;
+--------------------+
| Database           |
+--------------------+
| information_schema |
| your_db            |
+--------------------+
</pre><p></p>
<p>Beautiful!</p>
<h2>Passing Customizations in Compose</h2>
<p>This is all great, but we obviously don’t want a database called “your_db”, or a user called “your_user”. While we could change the Dockerfile to use the configurations we want, this misses the point.</p>
<p>In most Compose files, we are <em>not</em> referencing local Dockerfiles. Instead of “build”, we use the “image” statement and refer to a Docker image on the Hub. That way, we can reuse the work others have already put in. This also creates a problem: How do we pass customizations to 3rd party containers? Compose provides a subtle but powerful way to do this using the “environment” statement.</p>
<p>Both Dockerfiles and Compose files may specify environment variables to set in the container. You can use this to pass configuration details such as the database name, username, and password... but there’s a catch. The ENV statement in the Dockerfile sets environment variables during the build phase. These values persist into the run-phase of the container. Compose’s “environment” statement, on the other hand, may only set environment variables during the run phase. This means we can only use environment variables set in docker-compose.yml in a Dockerfile’s ENTRYPOINT, not in RUN statements.</p>
<p>Thankfully, we already replaced the ENTRYPOINT with a custom script. This makes things <em>much</em> easier for us! First, let’s update our docker-compose.yml with the environment variables we want to pass:</p>
<p><code></code></p>
<pre>
web:
   build: .docker/web
   ports:
      - "80:80"
   volumes:
      - docroot:/var/www
db:
   build: .docker/db
   ports:
      - 3306:3306
   environment:
      - MYSQL_DB=drupal8
      - MYSQL_USER=drupal
      - MYSQL_PASS=thisisawesome
</pre><p></p>
<p>The “environment” statement takes a list of one or more environment variables to pass to the container in <code>NAME_OF_VARIABLE=value_of_variable</code> format. Next, we need to update our ENTRYPOINT script, “mysql_run.sh”:</p>
<p><code></code></p>
<pre>
#!/usr/bin/env bash

set -m
set -e

MYSQL_DB=${MYSQL_DB:-your_db}
MYSQL_USER=${MYSQL_USER:-your_user}
MYSQL_PASS=${MYSQL_PASS:-your_password}

mysqld_safe &amp;

sleep 10

mysql -u root -e "CREATE DATABASE IF NOT EXISTS ${MYSQL_DB}"
mysql -u root -e "GRANT ALL ON ${MYSQL_DB}.* to \'${MYSQL_USER}\'@\'%\' IDENTIFIED BY \'${MYSQL_PASS}\'"
mysql -u root -e "FLUSH PRIVILEGES"

fg
</pre><p></p>
<p>You’ll notice that we inline the variables in our queries to the server that create the database and user. We also add some basic input protection. For each variable that we use, we define a default:</p>
<p><code></code></p>
<pre>
MYSQL_DB=${MYSQL_DB:-your_db}
</pre><p></p>
<p>This way, if there’s a typo in the Compose file, or an environment value is not set, the script falls back to the default. Now when we rebuild and up the containers, we get our custom database, user and password without having the modify the Dockerfile.</p>
<p><code></code></p>
<pre>
$ mysql -u drupal --password=thisisawesome -h docker.dev -P 3306   
Welcome to the MariaDB monitor.  Commands end with ; or \\g.
Your MySQL connection id is 6
Server version: 5.5.44-0+deb7u1 (Debian)

Copyright (c) 2000, 2015, Oracle, MariaDB Corporation Ab and others.

Type \'help;\' or \'\\h\' for help. Type \'\\c\' to clear the current input statement.

MySQL [(none)]&gt; show databases;
+--------------------+
| Database           |
+--------------------+
| information_schema |
| drupal8            |
+--------------------+
2 rows in set (0.00 sec)
</pre><p></p>
<h2>Summary</h2>
<p>We’ve expanded our Docker development environment a lot. We’ve not only added a new database container, but also created a custom ENTRYPOINT and added custom configuration in our Compose file. We’ve laid the foundation for an awesome, lightweight, and repeatable development environment. Next time, we’ll start to link together our containers and get our custom application code running.</p>
',
        'safe_summary' => '',
      ),
    ),
  ),
  'field_blog_image' => array(),
  'field_topic' => array(
    'und' => array(
      0 => array(
        'tid' => 1,
        'uuid' => '51e9afd5-0b71-46fb-8471-0aa7bad81c10',
      ),
    ),
  ),
  'path' => array(
    'pathauto' => 1,
  ),
  'cid' => 0,
  'last_comment_name' => NULL,
  'last_comment_uid' => 1,
  'comment_count' => 0,
  'flag_friend_access' => FALSE,
  'name' => 'admin',
  'picture' => 0,
  'data' => 'b:0;',
  'pathauto_perform_alias' => FALSE,
  'date' => '2015-09-04 01:23:14 +0000',
);
  $nodes[] = array(
  'uid' => 1,
  'title' => 'Docker from Scratch, Part 3: Entrypoints and Ports',
  'log' => '',
  'status' => 1,
  'comment' => 2,
  'promote' => 1,
  'sticky' => 0,
  'vuuid' => 'a06d6891-7443-4e94-9530-da1b39a352f9',
  'type' => 'blog',
  'language' => 'und',
  'created' => 1439766470,
  'tnid' => 0,
  'translate' => 0,
  'uuid' => 'ee575a2f-e54d-4c7a-a0d7-7b70561ee333',
  'revision_uid' => 1,
  'body' => array(
    'und' => array(
      0 => array(
        'value' => '<p><a href="/blog/1583/docker-scratch-part-2-dockerfiles">In the last post</a> we used the RUN statement in our Dockerfile to setup and install software in our container. This saves us the trouble of creating build scripts that we need to run each time we start the container. We still have to specify the command to run when we start the container. What we want to do is eliminate that so we have less to remember each time we use the container.</p>
<h2>Background vs. Foreground Processes</h2>
<p>When a container is run, only a single process is run within it. Containers are less like VMs in this way and more like sandboxed applications. The problem is, RUN only operates during the <em>build phase</em> of the container, not the <em>run phase</em>. Each time we have a RUN statement in our Dockerfile, Docker will start a new container from the most recent image, run the command, and if successful, create a new image overlaying the previous image. When we run the container, we used the Docker “run” command:</p>
<code><pre>
$ docker run -i -t aa0 /bin/bash
</pre></code>
<p>Where “aa0” are the first three characters of the image ID, and “/bin/bash” is the command to execute when running the container. We had used the ADD statement in the Dockerfile to install the Apache web server. What we want to do, however, is run the web server, not a bash shell. On the Debian Linux distribution we can run Apache using the “apachectl” command. Typically it takes the following form:</p>
<code><pre>
$ apachectl start
</pre></code>
<p>The command completes after a moment, and Apache is then running in the background. Now let’s try to run it with the image we built previously:</p>
<code><pre>
$ docker run -i -t aa0 apachectl start
apache2: Could not reliably determine the server\'s fully qualified domain name, using 172.17.0.7 for ServerName
</pre></code>
<p>That’s a non-fatal error Apache is giving us, so it should be up and running. </p>
<code><pre>
$ docker ps -a   
CONTAINER ID    IMAGE      COMMAND              CREATED             STATUS                    
9d0eab0934fe    aa0        "apachectl start"    2 minutes ago       Exited (0) 2 minutes ago
</pre></code>
<p>Why isn’t it running? When we told Docker to run the “apachectl” command, the Apache server did successfully start in the container. Then, apachectl exited and returned “0”. Since the command we specified is no longer running, Docker stopped the container. Remember, a container is “just a process.”
</p><p>
So how do we keep the container running? The solution is that we need to run Apache like we would a bash script -- in the foreground. While this isn’t something a normal sysadmin would do, you can run Apache in the foreground easily with the “-D” switch:</p>
<code><pre>
$ docker run -i -t aa0 apachectl -D FOREGROUND
</pre></code>
<p>This time, the command will <em>not</em> return immediately. If we open a new terminal prompt and list all running containers, we’ll find that we indeed have one container running now:</p>
<code><pre>
$ docker ps
CONTAINER ID     IMAGE    COMMAND                CREATED             STATUS              
059950c67e5b     aa0      "apachectl -D FOREGR   About a minute ago   Up About a minute
</pre></code>
This teaches us an important difference between building containers vs. building VMs. Since we’re only running one process rather than a whole operating system, we need to run just the process we need, not a command to start a daemon that runs in the background.</p>
<h2>Running Containers in the Background</h2>
<p>Right now our container is running in a terminal session on the host OS. We don’t want that. We’d rather just start the container in the background. Note, we want to start the container in the background, not the process running in the container! To do that we need to change the way we run our Docker command. So let’s Control-C out of the running container like we would any foreground CLI application and try again. 
</p><p>
We originally used the “-i” and “-t” switches on the Docker “run” command to run the container interactively. This time, we need to run the command with “-d”, or “detach”. This will run the container in the background:</p>
<code><pre>
$ docker run -d aa0 apachectl -D FOREGROUND
86414f5548dcecb83d80dec4ec9351a7697b23d11664738f8668167a127ec70e
</pre></code>
<p>The “run” command spits out the running container ID for us. We can verify that with the “ps” command:</p>
<code><pre>
$ docker ps 
CONTAINER ID        IMAGE         COMMAND                CREATED             STATUS
86414f5548dc        aa0           "apachectl -D FOREGR   36 seconds ago      Up 34 seconds
</pre></code>
<p>Nifty! Now we have the container in the background, and we have a free terminal session. But… how do we stop the container? As with processes, there’s the Docker “kill” command used to stop a running container:</p>
<code><pre>
$ docker kill 864
864
</pre></code>
<p>Docker repeats the container (partial) ID for every container we stop using the “kill” command. </p>
<h2>Entrypoints</h2>
<p>We still have to specify which command we want to start in the container on the CLI each time we start it up. That’s annoying! More importantly, it makes our container less repeatable. We want to just give our team a Dockerfile, and tell them to build and run it. We don’t want include instructions or READMEs. The solution, of course, is to add more stuff to the Dockerfile.
</p><p>
In addition to FROM, MAINTAINER, and ADD, there’s also CMD and ENTRYPOINT. CMD and ENTRYPOINT are more or less the same statement. You can only have one of each in your Dockerfile.  CMD has a few different forms: it can specify an executable, or just specify parameters for the executable in ENTRYPOINT. ENTRYPOINT always specifies the executable as its first argument.</p>
<code><pre>
CMD [“apachectl”, “-D”, “FOREGROUND”]
</pre></code>
<p>or</p>
<code><pre>
CMD [“-D”, “FOREGROUND”]
ENTRYPOINT [“apachectl”]
</pre></code>
<p>As you can see, each token in the full command is specified as a different argument to CMD and ENTRYPOINT and wrapped in double quotes. All arguments are enclosed within brackets. 
</p><p>
So what’s the difference between one CMD and a CMD and an ENTRYPOINT? It turns out, Docker maintains a default entrypoint, /bin/sh. When we used the Docker “run” command, it actually started a shell process for us, then ran the command we gave to Docker. So, our previous “run” command…</p>
<code><pre>
$ docker run -i -t aa0 apachectl -D FOREGROUND
</pre></code>
<p>…actually did this in the container:</p>
<code><pre>
$ /bin/sh -c “apachectl -D FOREGROUND”
</pre></code>
<p>We don’t need to run the default entrypoint if we don’t want to. We can replace it with our own using the ENTRYPOINT statement.</p> 
<h2>Running a Container with an Entrypoint</h2>
<p>At this point, our Dockerfile should specify what to execute when running the container:</p>
<code><pre>
FROM debian:wheezy
MAINTAINER your_email@example.com

RUN apt-get update
RUN apt-get install -y apache2

CMD ["-D", "FOREGROUND"]
ENTRYPOINT ["apachectl"]
</pre></code>
<p>We can easily update our images using the Docker “build” command:</p>
<code><pre>
$ docker build .

Sending build context to Docker daemon 2.048 kB
Sending build context to Docker daemon 
Step 0 : FROM debian:wheezy
 ---> 60c52dbe9d91
Step 1 : MAINTAINER your_email@example.com
 ---> Using cache
 ---> 64b0d7e8eef9
Step 2 : RUN apt-get update
 ---> Using cache
 ---> eefa2fcb15e7
Step 3 : RUN apt-get install -y apache2
 ---> Using cache
 ---> aa084388ac30
Step 4 : CMD -D FOREGROUND
 ---> Running in 32b9f66cf1e3
 ---> 239ae06b7d68
Removing intermediate container 32b9f66cf1e3
Step 5 : ENTRYPOINT apachectl
 ---> Running in 6ac785739695
 ---> 72b3cac68438
Removing intermediate container 6ac785739695
Successfully built 72b3cac68438
</pre></code>
<p>And now we can run it <em>without</em> specifying an entrypoint:</p>
<code><pre>
$ docker run -d 72b  
988bf0c8cdfdf88c42e3673a65597f78693c07b14070cd535962b13b36884560

$ docker ps 
CONTAINER ID        IMAGE         COMMAND                CREATED             STATUS              
988bf0c8cdfd        72b           "apachectl -D FOREGR   4 seconds ago       Up 3 seconds
</pre></code>
<p>So much easier!</p>
<h2>Finding the Container IP</h2>
<p>There’s still one more problem. If we try to visit the web server running in the container, what address do we navigate to? While the container -- the “guest” -- is running on our host machine, the guest doesn’t know that. It thinks it’s running on its own unique hardware. With a VM, we would point the web browser on the host OS to the IP address of the VM. When Docker is running on a Linux host, there is no VM.
</p><p>
The answer is actually pretty simple: it’s localhost. Remember, Docker containers are more like sandboxed applications than VMs. So if a process in the container needs to be network accessible, you would address the host system. Since we’re running this on our own workstation, localhost would be the correct answer.
</p><p>
What if you’re <em>not</em> running Docker on Linux? What if your host OS is Mac OS X or Windows? In that case, when you installed Docker you also installed a virtual machine -- boot2docker. The boot2docker VM is a lightweight Linux VM that can run all your docker containers. The answer as to what IP to use becomes obvious: it’s the boot2docker IP, just like you would with any VM.
</p><p>
How do you find the boot2docker IP? On installation, a DOCKER_HOST environment variable was defined for you, pointing to the IP of the boot2docker VM. This environment variable can become outdated, so it’s best to simply ask boot2docker for its IP:</p>
<code><pre>
$ boot2docker ip
192.168.59.103
</pre></code>
<p>Typing in the IP address all the time is annoying, though. On Mac OS and Linux, you can modify the /etc/hosts file to create an alias for the container:</p>
<code><pre>
192.168.59.103	docker.dev
</pre></code>
<p>Windows has the same hosts file, but buries it much more deeply in the operating system, at “C:\\Windows\\System32\\Drivers\\etc”. The format is the same. Once defined, you can easily go to http://docker.dev and view the web server running in your container.</p>
<h2>Exposing Ports of a Container</h2>
<p>When we navigate to the IP, however, we get a 404. What’s happening? Yes, our container is running, but we haven’t instructed Docker to expose the HTTP port to the host OS. To do that, we need to add an EXPOSE statement to our Dockerfile:</p>
<code><pre>
EXPOSE 80
</pre></code>
<p>After running “build” and “run” again, we can visit http://docker.dev and we finally get the “It works!” message from a default Apache installation. Awesome!</p>
<h2>Summary</h2>
<p>We came a long way in this post. We went from a minimal Dockerfile, to a complete, ready-to-use container with a handful of extra commands. We learned a little bit about Docker’s networking infrastructure. Next time, we’ll introduce a new layer of Docker technology that will make managing containers even easier, and use it to mount some files on our host OS in the process.</p>
<p><a href="/blog/1587/docker-scratch-part-4-compose-and-volumes">Read Part 4</a>.</p>',
        'summary' => '',
        'format' => 'full_html',
        'safe_value' => '<p><a href="/blog/1583/docker-scratch-part-2-dockerfiles">In the last post</a> we used the RUN statement in our Dockerfile to setup and install software in our container. This saves us the trouble of creating build scripts that we need to run each time we start the container. We still have to specify the command to run when we start the container. What we want to do is eliminate that so we have less to remember each time we use the container.</p>
<h2>Background vs. Foreground Processes</h2>
<p>When a container is run, only a single process is run within it. Containers are less like VMs in this way and more like sandboxed applications. The problem is, RUN only operates during the <em>build phase</em> of the container, not the <em>run phase</em>. Each time we have a RUN statement in our Dockerfile, Docker will start a new container from the most recent image, run the command, and if successful, create a new image overlaying the previous image. When we run the container, we used the Docker “run” command:</p>
<p><code></code></p>
<pre>
$ docker run -i -t aa0 /bin/bash
</pre><p></p>
<p>Where “aa0” are the first three characters of the image ID, and “/bin/bash” is the command to execute when running the container. We had used the ADD statement in the Dockerfile to install the Apache web server. What we want to do, however, is run the web server, not a bash shell. On the Debian Linux distribution we can run Apache using the “apachectl” command. Typically it takes the following form:</p>
<p><code></code></p>
<pre>
$ apachectl start
</pre><p></p>
<p>The command completes after a moment, and Apache is then running in the background. Now let’s try to run it with the image we built previously:</p>
<p><code></code></p>
<pre>
$ docker run -i -t aa0 apachectl start
apache2: Could not reliably determine the server\'s fully qualified domain name, using 172.17.0.7 for ServerName
</pre><p></p>
<p>That’s a non-fatal error Apache is giving us, so it should be up and running. </p>
<p><code></code></p>
<pre>
$ docker ps -a   
CONTAINER ID    IMAGE      COMMAND              CREATED             STATUS                    
9d0eab0934fe    aa0        "apachectl start"    2 minutes ago       Exited (0) 2 minutes ago
</pre><p></p>
<p>Why isn’t it running? When we told Docker to run the “apachectl” command, the Apache server did successfully start in the container. Then, apachectl exited and returned “0”. Since the command we specified is no longer running, Docker stopped the container. Remember, a container is “just a process.”
</p>
<p>
So how do we keep the container running? The solution is that we need to run Apache like we would a bash script -- in the foreground. While this isn’t something a normal sysadmin would do, you can run Apache in the foreground easily with the “-D” switch:</p>
<p><code></code></p>
<pre>
$ docker run -i -t aa0 apachectl -D FOREGROUND
</pre><p></p>
<p>This time, the command will <em>not</em> return immediately. If we open a new terminal prompt and list all running containers, we’ll find that we indeed have one container running now:</p>
<p><code></code></p>
<pre>
$ docker ps
CONTAINER ID     IMAGE    COMMAND                CREATED             STATUS              
059950c67e5b     aa0      "apachectl -D FOREGR   About a minute ago   Up About a minute
</pre><p><br />
This teaches us an important difference between building containers vs. building VMs. Since we’re only running one process rather than a whole operating system, we need to run just the process we need, not a command to start a daemon that runs in the background.</p>
<h2>Running Containers in the Background</h2>
<p>Right now our container is running in a terminal session on the host OS. We don’t want that. We’d rather just start the container in the background. Note, we want to start the container in the background, not the process running in the container! To do that we need to change the way we run our Docker command. So let’s Control-C out of the running container like we would any foreground CLI application and try again.
</p>
<p>
We originally used the “-i” and “-t” switches on the Docker “run” command to run the container interactively. This time, we need to run the command with “-d”, or “detach”. This will run the container in the background:</p>
<p><code></code></p>
<pre>
$ docker run -d aa0 apachectl -D FOREGROUND
86414f5548dcecb83d80dec4ec9351a7697b23d11664738f8668167a127ec70e
</pre><p></p>
<p>The “run” command spits out the running container ID for us. We can verify that with the “ps” command:</p>
<p><code></code></p>
<pre>
$ docker ps 
CONTAINER ID        IMAGE         COMMAND                CREATED             STATUS
86414f5548dc        aa0           "apachectl -D FOREGR   36 seconds ago      Up 34 seconds
</pre><p></p>
<p>Nifty! Now we have the container in the background, and we have a free terminal session. But… how do we stop the container? As with processes, there’s the Docker “kill” command used to stop a running container:</p>
<p><code></code></p>
<pre>
$ docker kill 864
864
</pre><p></p>
<p>Docker repeats the container (partial) ID for every container we stop using the “kill” command. </p>
<h2>Entrypoints</h2>
<p>We still have to specify which command we want to start in the container on the CLI each time we start it up. That’s annoying! More importantly, it makes our container less repeatable. We want to just give our team a Dockerfile, and tell them to build and run it. We don’t want include instructions or READMEs. The solution, of course, is to add more stuff to the Dockerfile.
</p>
<p>
In addition to FROM, MAINTAINER, and ADD, there’s also CMD and ENTRYPOINT. CMD and ENTRYPOINT are more or less the same statement. You can only have one of each in your Dockerfile.  CMD has a few different forms: it can specify an executable, or just specify parameters for the executable in ENTRYPOINT. ENTRYPOINT always specifies the executable as its first argument.</p>
<p><code></code></p>
<pre>
CMD [“apachectl”, “-D”, “FOREGROUND”]
</pre><p></p>
<p>or</p>
<p><code></code></p>
<pre>
CMD [“-D”, “FOREGROUND”]
ENTRYPOINT [“apachectl”]
</pre><p></p>
<p>As you can see, each token in the full command is specified as a different argument to CMD and ENTRYPOINT and wrapped in double quotes. All arguments are enclosed within brackets.
</p>
<p>
So what’s the difference between one CMD and a CMD and an ENTRYPOINT? It turns out, Docker maintains a default entrypoint, /bin/sh. When we used the Docker “run” command, it actually started a shell process for us, then ran the command we gave to Docker. So, our previous “run” command…</p>
<p><code></code></p>
<pre>
$ docker run -i -t aa0 apachectl -D FOREGROUND
</pre><p></p>
<p>…actually did this in the container:</p>
<p><code></code></p>
<pre>
$ /bin/sh -c “apachectl -D FOREGROUND”
</pre><p></p>
<p>We don’t need to run the default entrypoint if we don’t want to. We can replace it with our own using the ENTRYPOINT statement.</p>
<h2>Running a Container with an Entrypoint</h2>
<p>At this point, our Dockerfile should specify what to execute when running the container:</p>
<p><code></code></p>
<pre>
FROM debian:wheezy
MAINTAINER your_email@example.com

RUN apt-get update
RUN apt-get install -y apache2

CMD ["-D", "FOREGROUND"]
ENTRYPOINT ["apachectl"]
</pre><p></p>
<p>We can easily update our images using the Docker “build” command:</p>
<p><code></code></p>
<pre>
$ docker build .

Sending build context to Docker daemon 2.048 kB
Sending build context to Docker daemon 
Step 0 : FROM debian:wheezy
 ---&gt; 60c52dbe9d91
Step 1 : MAINTAINER your_email@example.com
 ---&gt; Using cache
 ---&gt; 64b0d7e8eef9
Step 2 : RUN apt-get update
 ---&gt; Using cache
 ---&gt; eefa2fcb15e7
Step 3 : RUN apt-get install -y apache2
 ---&gt; Using cache
 ---&gt; aa084388ac30
Step 4 : CMD -D FOREGROUND
 ---&gt; Running in 32b9f66cf1e3
 ---&gt; 239ae06b7d68
Removing intermediate container 32b9f66cf1e3
Step 5 : ENTRYPOINT apachectl
 ---&gt; Running in 6ac785739695
 ---&gt; 72b3cac68438
Removing intermediate container 6ac785739695
Successfully built 72b3cac68438
</pre><p></p>
<p>And now we can run it <em>without</em> specifying an entrypoint:</p>
<p><code></code></p>
<pre>
$ docker run -d 72b  
988bf0c8cdfdf88c42e3673a65597f78693c07b14070cd535962b13b36884560

$ docker ps 
CONTAINER ID        IMAGE         COMMAND                CREATED             STATUS              
988bf0c8cdfd        72b           "apachectl -D FOREGR   4 seconds ago       Up 3 seconds
</pre><p></p>
<p>So much easier!</p>
<h2>Finding the Container IP</h2>
<p>There’s still one more problem. If we try to visit the web server running in the container, what address do we navigate to? While the container -- the “guest” -- is running on our host machine, the guest doesn’t know that. It thinks it’s running on its own unique hardware. With a VM, we would point the web browser on the host OS to the IP address of the VM. When Docker is running on a Linux host, there is no VM.
</p>
<p>
The answer is actually pretty simple: it’s localhost. Remember, Docker containers are more like sandboxed applications than VMs. So if a process in the container needs to be network accessible, you would address the host system. Since we’re running this on our own workstation, localhost would be the correct answer.
</p>
<p>
What if you’re <em>not</em> running Docker on Linux? What if your host OS is Mac OS X or Windows? In that case, when you installed Docker you also installed a virtual machine -- boot2docker. The boot2docker VM is a lightweight Linux VM that can run all your docker containers. The answer as to what IP to use becomes obvious: it’s the boot2docker IP, just like you would with any VM.
</p>
<p>
How do you find the boot2docker IP? On installation, a DOCKER_HOST environment variable was defined for you, pointing to the IP of the boot2docker VM. This environment variable can become outdated, so it’s best to simply ask boot2docker for its IP:</p>
<p><code></code></p>
<pre>
$ boot2docker ip
192.168.59.103
</pre><p></p>
<p>Typing in the IP address all the time is annoying, though. On Mac OS and Linux, you can modify the /etc/hosts file to create an alias for the container:</p>
<p><code></code></p>
<pre>
192.168.59.103	docker.dev
</pre><p></p>
<p>Windows has the same hosts file, but buries it much more deeply in the operating system, at “C:\\Windows\\System32\\Drivers\\etc”. The format is the same. Once defined, you can easily go to <a href="http://docker.dev">http://docker.dev</a> and view the web server running in your container.</p>
<h2>Exposing Ports of a Container</h2>
<p>When we navigate to the IP, however, we get a 404. What’s happening? Yes, our container is running, but we haven’t instructed Docker to expose the HTTP port to the host OS. To do that, we need to add an EXPOSE statement to our Dockerfile:</p>
<p><code></code></p>
<pre>
EXPOSE 80
</pre><p></p>
<p>After running “build” and “run” again, we can visit <a href="http://docker.dev">http://docker.dev</a> and we finally get the “It works!” message from a default Apache installation. Awesome!</p>
<h2>Summary</h2>
<p>We came a long way in this post. We went from a minimal Dockerfile, to a complete, ready-to-use container with a handful of extra commands. We learned a little bit about Docker’s networking infrastructure. Next time, we’ll introduce a new layer of Docker technology that will make managing containers even easier, and use it to mount some files on our host OS in the process.</p>
<p><a href="/blog/1587/docker-scratch-part-4-compose-and-volumes">Read Part 4</a>.</p>
',
        'safe_summary' => '',
      ),
    ),
  ),
  'field_blog_image' => array(),
  'field_topic' => array(
    'und' => array(
      0 => array(
        'tid' => 1,
        'uuid' => '51e9afd5-0b71-46fb-8471-0aa7bad81c10',
      ),
    ),
  ),
  'path' => array(
    'pathauto' => 1,
  ),
  'cid' => 0,
  'last_comment_name' => NULL,
  'last_comment_uid' => 1,
  'comment_count' => 0,
  'flag_friend_access' => FALSE,
  'name' => 'admin',
  'picture' => 0,
  'data' => 'b:0;',
  'pathauto_perform_alias' => FALSE,
  'date' => '2015-08-16 23:07:50 +0000',
);
  return $nodes;
}
