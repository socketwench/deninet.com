//     Underscore.js 1.7.0
//     http://underscorejs.org
//     (c) 2009-2014 Jeremy Ashkenas, DocumentCloud and Investigative Reporters & Editors
//     Underscore may be freely distributed under the MIT license.

(function(){var e=this;var t=e._;var n=Array.prototype,r=Object.prototype,i=Function.prototype;var s=n.push,o=n.slice,u=n.concat,a=r.toString,f=r.hasOwnProperty;var l=Array.isArray,c=Object.keys,h=i.bind;var p=function(e){if(e instanceof p)return e;if(!(this instanceof p))return new p(e);this._wrapped=e};if(typeof exports!=="undefined"){if(typeof module!=="undefined"&&module.exports){exports=module.exports=p}exports._=p}else{e._=p}p.VERSION="1.7.0";var d=function(e,t,n){if(t===void 0)return e;switch(n==null?3:n){case 1:return function(n){return e.call(t,n)};case 2:return function(n,r){return e.call(t,n,r)};case 3:return function(n,r,i){return e.call(t,n,r,i)};case 4:return function(n,r,i,s){return e.call(t,n,r,i,s)}}return function(){return e.apply(t,arguments)}};p.iteratee=function(e,t,n){if(e==null)return p.identity;if(p.isFunction(e))return d(e,t,n);if(p.isObject(e))return p.matches(e);return p.property(e)};p.each=p.forEach=function(e,t,n){if(e==null)return e;t=d(t,n);var r,i=e.length;if(i===+i){for(r=0;r<i;r++){t(e[r],r,e)}}else{var s=p.keys(e);for(r=0,i=s.length;r<i;r++){t(e[s[r]],s[r],e)}}return e};p.map=p.collect=function(e,t,n){if(e==null)return[];t=p.iteratee(t,n);var r=e.length!==+e.length&&p.keys(e),i=(r||e).length,s=Array(i),o;for(var u=0;u<i;u++){o=r?r[u]:u;s[u]=t(e[o],o,e)}return s};var v="Reduce of empty array with no initial value";p.reduce=p.foldl=p.inject=function(e,t,n,r){if(e==null)e=[];t=d(t,r,4);var i=e.length!==+e.length&&p.keys(e),s=(i||e).length,o=0,u;if(arguments.length<3){if(!s)throw new TypeError(v);n=e[i?i[o++]:o++]}for(;o<s;o++){u=i?i[o]:o;n=t(n,e[u],u,e)}return n};p.reduceRight=p.foldr=function(e,t,n,r){if(e==null)e=[];t=d(t,r,4);var i=e.length!==+e.length&&p.keys(e),s=(i||e).length,o;if(arguments.length<3){if(!s)throw new TypeError(v);n=e[i?i[--s]:--s]}while(s--){o=i?i[s]:s;n=t(n,e[o],o,e)}return n};p.find=p.detect=function(e,t,n){var r;t=p.iteratee(t,n);p.some(e,function(e,n,i){if(t(e,n,i)){r=e;return true}});return r};p.filter=p.select=function(e,t,n){var r=[];if(e==null)return r;t=p.iteratee(t,n);p.each(e,function(e,n,i){if(t(e,n,i))r.push(e)});return r};p.reject=function(e,t,n){return p.filter(e,p.negate(p.iteratee(t)),n)};p.every=p.all=function(e,t,n){if(e==null)return true;t=p.iteratee(t,n);var r=e.length!==+e.length&&p.keys(e),i=(r||e).length,s,o;for(s=0;s<i;s++){o=r?r[s]:s;if(!t(e[o],o,e))return false}return true};p.some=p.any=function(e,t,n){if(e==null)return false;t=p.iteratee(t,n);var r=e.length!==+e.length&&p.keys(e),i=(r||e).length,s,o;for(s=0;s<i;s++){o=r?r[s]:s;if(t(e[o],o,e))return true}return false};p.contains=p.include=function(e,t){if(e==null)return false;if(e.length!==+e.length)e=p.values(e);return p.indexOf(e,t)>=0};p.invoke=function(e,t){var n=o.call(arguments,2);var r=p.isFunction(t);return p.map(e,function(e){return(r?t:e[t]).apply(e,n)})};p.pluck=function(e,t){return p.map(e,p.property(t))};p.where=function(e,t){return p.filter(e,p.matches(t))};p.findWhere=function(e,t){return p.find(e,p.matches(t))};p.max=function(e,t,n){var r=-Infinity,i=-Infinity,s,o;if(t==null&&e!=null){e=e.length===+e.length?e:p.values(e);for(var u=0,a=e.length;u<a;u++){s=e[u];if(s>r){r=s}}}else{t=p.iteratee(t,n);p.each(e,function(e,n,s){o=t(e,n,s);if(o>i||o===-Infinity&&r===-Infinity){r=e;i=o}})}return r};p.min=function(e,t,n){var r=Infinity,i=Infinity,s,o;if(t==null&&e!=null){e=e.length===+e.length?e:p.values(e);for(var u=0,a=e.length;u<a;u++){s=e[u];if(s<r){r=s}}}else{t=p.iteratee(t,n);p.each(e,function(e,n,s){o=t(e,n,s);if(o<i||o===Infinity&&r===Infinity){r=e;i=o}})}return r};p.shuffle=function(e){var t=e&&e.length===+e.length?e:p.values(e);var n=t.length;var r=Array(n);for(var i=0,s;i<n;i++){s=p.random(0,i);if(s!==i)r[i]=r[s];r[s]=t[i]}return r};p.sample=function(e,t,n){if(t==null||n){if(e.length!==+e.length)e=p.values(e);return e[p.random(e.length-1)]}return p.shuffle(e).slice(0,Math.max(0,t))};p.sortBy=function(e,t,n){t=p.iteratee(t,n);return p.pluck(p.map(e,function(e,n,r){return{value:e,index:n,criteria:t(e,n,r)}}).sort(function(e,t){var n=e.criteria;var r=t.criteria;if(n!==r){if(n>r||n===void 0)return 1;if(n<r||r===void 0)return-1}return e.index-t.index}),"value")};var m=function(e){return function(t,n,r){var i={};n=p.iteratee(n,r);p.each(t,function(r,s){var o=n(r,s,t);e(i,r,o)});return i}};p.groupBy=m(function(e,t,n){if(p.has(e,n))e[n].push(t);else e[n]=[t]});p.indexBy=m(function(e,t,n){e[n]=t});p.countBy=m(function(e,t,n){if(p.has(e,n))e[n]++;else e[n]=1});p.sortedIndex=function(e,t,n,r){n=p.iteratee(n,r,1);var i=n(t);var s=0,o=e.length;while(s<o){var u=s+o>>>1;if(n(e[u])<i)s=u+1;else o=u}return s};p.toArray=function(e){if(!e)return[];if(p.isArray(e))return o.call(e);if(e.length===+e.length)return p.map(e,p.identity);return p.values(e)};p.size=function(e){if(e==null)return 0;return e.length===+e.length?e.length:p.keys(e).length};p.partition=function(e,t,n){t=p.iteratee(t,n);var r=[],i=[];p.each(e,function(e,n,s){(t(e,n,s)?r:i).push(e)});return[r,i]};p.first=p.head=p.take=function(e,t,n){if(e==null)return void 0;if(t==null||n)return e[0];if(t<0)return[];return o.call(e,0,t)};p.initial=function(e,t,n){return o.call(e,0,Math.max(0,e.length-(t==null||n?1:t)))};p.last=function(e,t,n){if(e==null)return void 0;if(t==null||n)return e[e.length-1];return o.call(e,Math.max(e.length-t,0))};p.rest=p.tail=p.drop=function(e,t,n){return o.call(e,t==null||n?1:t)};p.compact=function(e){return p.filter(e,p.identity)};var g=function(e,t,n,r){if(t&&p.every(e,p.isArray)){return u.apply(r,e)}for(var i=0,o=e.length;i<o;i++){var a=e[i];if(!p.isArray(a)&&!p.isArguments(a)){if(!n)r.push(a)}else if(t){s.apply(r,a)}else{g(a,t,n,r)}}return r};p.flatten=function(e,t){return g(e,t,false,[])};p.without=function(e){return p.difference(e,o.call(arguments,1))};p.uniq=p.unique=function(e,t,n,r){if(e==null)return[];if(!p.isBoolean(t)){r=n;n=t;t=false}if(n!=null)n=p.iteratee(n,r);var i=[];var s=[];for(var o=0,u=e.length;o<u;o++){var a=e[o];if(t){if(!o||s!==a)i.push(a);s=a}else if(n){var f=n(a,o,e);if(p.indexOf(s,f)<0){s.push(f);i.push(a)}}else if(p.indexOf(i,a)<0){i.push(a)}}return i};p.union=function(){return p.uniq(g(arguments,true,true,[]))};p.intersection=function(e){if(e==null)return[];var t=[];var n=arguments.length;for(var r=0,i=e.length;r<i;r++){var s=e[r];if(p.contains(t,s))continue;for(var o=1;o<n;o++){if(!p.contains(arguments[o],s))break}if(o===n)t.push(s)}return t};p.difference=function(e){var t=g(o.call(arguments,1),true,true,[]);return p.filter(e,function(e){return!p.contains(t,e)})};p.zip=function(e){if(e==null)return[];var t=p.max(arguments,"length").length;var n=Array(t);for(var r=0;r<t;r++){n[r]=p.pluck(arguments,r)}return n};p.object=function(e,t){if(e==null)return{};var n={};for(var r=0,i=e.length;r<i;r++){if(t){n[e[r]]=t[r]}else{n[e[r][0]]=e[r][1]}}return n};p.indexOf=function(e,t,n){if(e==null)return-1;var r=0,i=e.length;if(n){if(typeof n=="number"){r=n<0?Math.max(0,i+n):n}else{r=p.sortedIndex(e,t);return e[r]===t?r:-1}}for(;r<i;r++)if(e[r]===t)return r;return-1};p.lastIndexOf=function(e,t,n){if(e==null)return-1;var r=e.length;if(typeof n=="number"){r=n<0?r+n+1:Math.min(r,n+1)}while(--r>=0)if(e[r]===t)return r;return-1};p.range=function(e,t,n){if(arguments.length<=1){t=e||0;e=0}n=n||1;var r=Math.max(Math.ceil((t-e)/n),0);var i=Array(r);for(var s=0;s<r;s++,e+=n){i[s]=e}return i};var y=function(){};p.bind=function(e,t){var n,r;if(h&&e.bind===h)return h.apply(e,o.call(arguments,1));if(!p.isFunction(e))throw new TypeError("Bind must be called on a function");n=o.call(arguments,2);r=function(){if(!(this instanceof r))return e.apply(t,n.concat(o.call(arguments)));y.prototype=e.prototype;var i=new y;y.prototype=null;var s=e.apply(i,n.concat(o.call(arguments)));if(p.isObject(s))return s;return i};return r};p.partial=function(e){var t=o.call(arguments,1);return function(){var n=0;var r=t.slice();for(var i=0,s=r.length;i<s;i++){if(r[i]===p)r[i]=arguments[n++]}while(n<arguments.length)r.push(arguments[n++]);return e.apply(this,r)}};p.bindAll=function(e){var t,n=arguments.length,r;if(n<=1)throw new Error("bindAll must be passed function names");for(t=1;t<n;t++){r=arguments[t];e[r]=p.bind(e[r],e)}return e};p.memoize=function(e,t){var n=function(r){var i=n.cache;var s=t?t.apply(this,arguments):r;if(!p.has(i,s))i[s]=e.apply(this,arguments);return i[s]};n.cache={};return n};p.delay=function(e,t){var n=o.call(arguments,2);return setTimeout(function(){return e.apply(null,n)},t)};p.defer=function(e){return p.delay.apply(p,[e,1].concat(o.call(arguments,1)))};p.throttle=function(e,t,n){var r,i,s;var o=null;var u=0;if(!n)n={};var a=function(){u=n.leading===false?0:p.now();o=null;s=e.apply(r,i);if(!o)r=i=null};return function(){var f=p.now();if(!u&&n.leading===false)u=f;var l=t-(f-u);r=this;i=arguments;if(l<=0||l>t){clearTimeout(o);o=null;u=f;s=e.apply(r,i);if(!o)r=i=null}else if(!o&&n.trailing!==false){o=setTimeout(a,l)}return s}};p.debounce=function(e,t,n){var r,i,s,o,u;var a=function(){var f=p.now()-o;if(f<t&&f>0){r=setTimeout(a,t-f)}else{r=null;if(!n){u=e.apply(s,i);if(!r)s=i=null}}};return function(){s=this;i=arguments;o=p.now();var f=n&&!r;if(!r)r=setTimeout(a,t);if(f){u=e.apply(s,i);s=i=null}return u}};p.wrap=function(e,t){return p.partial(t,e)};p.negate=function(e){return function(){return!e.apply(this,arguments)}};p.compose=function(){var e=arguments;var t=e.length-1;return function(){var n=t;var r=e[t].apply(this,arguments);while(n--)r=e[n].call(this,r);return r}};p.after=function(e,t){return function(){if(--e<1){return t.apply(this,arguments)}}};p.before=function(e,t){var n;return function(){if(--e>0){n=t.apply(this,arguments)}else{t=null}return n}};p.once=p.partial(p.before,2);p.keys=function(e){if(!p.isObject(e))return[];if(c)return c(e);var t=[];for(var n in e)if(p.has(e,n))t.push(n);return t};p.values=function(e){var t=p.keys(e);var n=t.length;var r=Array(n);for(var i=0;i<n;i++){r[i]=e[t[i]]}return r};p.pairs=function(e){var t=p.keys(e);var n=t.length;var r=Array(n);for(var i=0;i<n;i++){r[i]=[t[i],e[t[i]]]}return r};p.invert=function(e){var t={};var n=p.keys(e);for(var r=0,i=n.length;r<i;r++){t[e[n[r]]]=n[r]}return t};p.functions=p.methods=function(e){var t=[];for(var n in e){if(p.isFunction(e[n]))t.push(n)}return t.sort()};p.extend=function(e){if(!p.isObject(e))return e;var t,n;for(var r=1,i=arguments.length;r<i;r++){t=arguments[r];for(n in t){if(f.call(t,n)){e[n]=t[n]}}}return e};p.pick=function(e,t,n){var r={},i;if(e==null)return r;if(p.isFunction(t)){t=d(t,n);for(i in e){var s=e[i];if(t(s,i,e))r[i]=s}}else{var a=u.apply([],o.call(arguments,1));e=new Object(e);for(var f=0,l=a.length;f<l;f++){i=a[f];if(i in e)r[i]=e[i]}}return r};p.omit=function(e,t,n){if(p.isFunction(t)){t=p.negate(t)}else{var r=p.map(u.apply([],o.call(arguments,1)),String);t=function(e,t){return!p.contains(r,t)}}return p.pick(e,t,n)};p.defaults=function(e){if(!p.isObject(e))return e;for(var t=1,n=arguments.length;t<n;t++){var r=arguments[t];for(var i in r){if(e[i]===void 0)e[i]=r[i]}}return e};p.clone=function(e){if(!p.isObject(e))return e;return p.isArray(e)?e.slice():p.extend({},e)};p.tap=function(e,t){t(e);return e};var b=function(e,t,n,r){if(e===t)return e!==0||1/e===1/t;if(e==null||t==null)return e===t;if(e instanceof p)e=e._wrapped;if(t instanceof p)t=t._wrapped;var i=a.call(e);if(i!==a.call(t))return false;switch(i){case"[object RegExp]":case"[object String]":return""+e===""+t;case"[object Number]":if(+e!==+e)return+t!==+t;return+e===0?1/+e===1/t:+e===+t;case"[object Date]":case"[object Boolean]":return+e===+t}if(typeof e!="object"||typeof t!="object")return false;var s=n.length;while(s--){if(n[s]===e)return r[s]===t}var o=e.constructor,u=t.constructor;if(o!==u&&"constructor"in e&&"constructor"in t&&!(p.isFunction(o)&&o instanceof o&&p.isFunction(u)&&u instanceof u)){return false}n.push(e);r.push(t);var f,l;if(i==="[object Array]"){f=e.length;l=f===t.length;if(l){while(f--){if(!(l=b(e[f],t[f],n,r)))break}}}else{var c=p.keys(e),h;f=c.length;l=p.keys(t).length===f;if(l){while(f--){h=c[f];if(!(l=p.has(t,h)&&b(e[h],t[h],n,r)))break}}}n.pop();r.pop();return l};p.isEqual=function(e,t){return b(e,t,[],[])};p.isEmpty=function(e){if(e==null)return true;if(p.isArray(e)||p.isString(e)||p.isArguments(e))return e.length===0;for(var t in e)if(p.has(e,t))return false;return true};p.isElement=function(e){return!!(e&&e.nodeType===1)};p.isArray=l||function(e){return a.call(e)==="[object Array]"};p.isObject=function(e){var t=typeof e;return t==="function"||t==="object"&&!!e};p.each(["Arguments","Function","String","Number","Date","RegExp"],function(e){p["is"+e]=function(t){return a.call(t)==="[object "+e+"]"}});if(!p.isArguments(arguments)){p.isArguments=function(e){return p.has(e,"callee")}}if(typeof /./!=="function"){p.isFunction=function(e){return typeof e=="function"||false}}p.isFinite=function(e){return isFinite(e)&&!isNaN(parseFloat(e))};p.isNaN=function(e){return p.isNumber(e)&&e!==+e};p.isBoolean=function(e){return e===true||e===false||a.call(e)==="[object Boolean]"};p.isNull=function(e){return e===null};p.isUndefined=function(e){return e===void 0};p.has=function(e,t){return e!=null&&f.call(e,t)};p.noConflict=function(){e._=t;return this};p.identity=function(e){return e};p.constant=function(e){return function(){return e}};p.noop=function(){};p.property=function(e){return function(t){return t[e]}};p.matches=function(e){var t=p.pairs(e),n=t.length;return function(e){if(e==null)return!n;e=new Object(e);for(var r=0;r<n;r++){var i=t[r],s=i[0];if(i[1]!==e[s]||!(s in e))return false}return true}};p.times=function(e,t,n){var r=Array(Math.max(0,e));t=d(t,n,1);for(var i=0;i<e;i++)r[i]=t(i);return r};p.random=function(e,t){if(t==null){t=e;e=0}return e+Math.floor(Math.random()*(t-e+1))};p.now=Date.now||function(){return(new Date).getTime()};var w={"&":"&","<":"&lt;",">":"&gt;",'"':"&quot;","'":"&#x27;","`":"&#x60;"};var E=p.invert(w);var S=function(e){var t=function(t){return e[t]};var n="(?:"+p.keys(e).join("|")+")";var r=RegExp(n);var i=RegExp(n,"g");return function(e){e=e==null?"":""+e;return r.test(e)?e.replace(i,t):e}};p.escape=S(w);p.unescape=S(E);p.result=function(e,t){if(e==null)return void 0;var n=e[t];return p.isFunction(n)?e[t]():n};var x=0;p.uniqueId=function(e){var t=++x+"";return e?e+t:t};p.templateSettings={evaluate:/<%([\s\S]+?)%>/g,interpolate:/<%=([\s\S]+?)%>/g,escape:/<%-([\s\S]+?)%>/g};var T=/(.)^/;var N={"'":"'","\\":"\\","\r":"r","\n":"n","\u2028":"u2028","\u2029":"u2029"};var C=/\\|'|\r|\n|\u2028|\u2029/g;var k=function(e){return"\\"+N[e]};p.template=function(e,t,n){if(!t&&n)t=n;t=p.defaults({},t,p.templateSettings);var r=RegExp([(t.escape||T).source,(t.interpolate||T).source,(t.evaluate||T).source].join("|")+"|$","g");var i=0;var s="__p+='";e.replace(r,function(t,n,r,o,u){s+=e.slice(i,u).replace(C,k);i=u+t.length;if(n){s+="'+\n((__t=("+n+"))==null?'':_.escape(__t))+\n'"}else if(r){s+="'+\n((__t=("+r+"))==null?'':__t)+\n'"}else if(o){s+="';\n"+o+"\n__p+='"}return t});s+="';\n";if(!t.variable)s="with(obj||{}){\n"+s+"}\n";s="var __t,__p='',__j=Array.prototype.join,"+"print=function(){__p+=__j.call(arguments,'');};\n"+s+"return __p;\n";try{var o=new Function(t.variable||"obj","_",s)}catch(u){u.source=s;throw u}var a=function(e){return o.call(this,e,p)};var f=t.variable||"obj";a.source="function("+f+"){\n"+s+"}";return a};p.chain=function(e){var t=p(e);t._chain=true;return t};var L=function(e){return this._chain?p(e).chain():e};p.mixin=function(e){p.each(p.functions(e),function(t){var n=p[t]=e[t];p.prototype[t]=function(){var e=[this._wrapped];s.apply(e,arguments);return L.call(this,n.apply(p,e))}})};p.mixin(p);p.each(["pop","push","reverse","shift","sort","splice","unshift"],function(e){var t=n[e];p.prototype[e]=function(){var n=this._wrapped;t.apply(n,arguments);if((e==="shift"||e==="splice")&&n.length===0)delete n[0];return L.call(this,n)}});p.each(["concat","join","slice"],function(e){var t=n[e];p.prototype[e]=function(){return L.call(this,t.apply(this._wrapped,arguments))}});p.prototype.value=function(){return this._wrapped};if(typeof define==="function"&&define.amd){define("underscore",[],function(){return p})}}).call(this);