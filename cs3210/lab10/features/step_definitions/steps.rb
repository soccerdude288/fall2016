Before do
end

Given (/^the file "([^"]*)" should include:$/) do |file, string|
	step "I run `sed 's/^[[:blank:]]//g' -i #{file}`"
	step "I run `sed 's/[[:blank:]]$//g' -i #{file}`"
	step "I run `sed 's/[[:blank:]][[:blank:]]*/ /g' -i #{file}`"
	@strArray = string.to_s.split("\n")
	#puts "The string is \n#{@strArray}"
	@strArray.map! { |s| s.lstrip.rstrip.gsub(/[[:blank:]][[:blank:]]*/, ' ') }
	@newStr = @strArray.join("\n")
	#puts "The new string is \n#{@newStr}"
	step %{the file "#{file}" should contain:}, @newStr 
end

Given /^the output should contain the current date and time/ do
	puts "The time right now is #{@nowtime}"
	@nowtime = Time.now.asctime
	step "I run `userinfo -t`"
	step "the output should contain \"#{@nowtime}\""
end

Given /^the output should match that from getpwnam for (.*)$/ do |u|
	@pwnam = Etc.getpwnam(u)
	puts "pwnam for #{u} contains #{@pwnam}"
	step "the output should contain \"username: #{@pwnam.name}\""
	step "the output should contain \"user ID: #{@pwnam.uid}\""
	step "the output should contain \"group ID: #{@pwnam.gid}\""
	step "the output should contain \"home directory: #{@pwnam.dir}\""
	step "the output should contain \"shell: #{@pwnam.shell}\""
	step "the output should contain \"gecos information: #{@pwnam.gecos}\""
end


Given /^the output should contain PWD$/ do 
	if @dirs == nil then
		@dirs = ["tmp", "aruba"]
	end	
	#puts ENV['PWD']
	#puts ENV['HOME']
	#puts @dirs.join("/")
	#step "the output should match /" + Regexp.escape(ENV['PWD']) + "/"
	step "the output should contain \"" +  ENV['PWD'] + "/" + @dirs.join("/") + "\""
end

Given /^the output should contain HOME$/ do 
	puts "The home directory is #{ENV['HOME']}"
	#puts @dirs.join("/")
	#step "the output should match /" + Regexp.escape(ENV['HOME']) + "$/"
	step "the output should contain \"" +  ENV['HOME'] + "\n" + "\""
	#step "the output should not contain \"" +  ENV['HOME'] + "/" + "\""
end

Given /^the output should contain the host name$/ do
	#puts "The Host Name here is " + ENV['PWD']
	#step "the output should match /" + Regexp.escape(ENV['PWD']) + "/"
	#step "the output should contain \"" + #{str} + " " + ENV['HOSTNAME'] + "\""
	#step "the output should contain \"icarus\""
	@host = `hostname`
	puts "The Host Name here is " + @host 
	step "the output should contain \"" + @host + "\""
end

Given /^the output should contain the pid\/ppid$/ do
	@mypid = $?.pid
	@myppid = Process.pid
	puts "The pid is " + "#{@mypid}" + " and the PPID is " + "#{@myppid}"
	step "the output should contain \"" + "#{@mypid}/#{@myppid}" + "\""
end

Given /^there is only one (.*) running$/ do |pgm|
	@cnt = `ps --no-header -C #{pgm} | wc -l`
	if @cnt != "1" 
		@psout = `ps -C #{pgm}`
		raise "There are more than one #{pgm} programs running.\n#{@psout}"
	end
end

Given /^(.*) points are awarded/ do |points|
	#puts "#{points} points are now awarded!!!"
	$total_points += points.to_i
end

Given /^dot is replaced with PWD\/(.*)$/ do |outputfile|
	step "the output should contain \"copy #{outputfile} #{ENV['PWD']}\/#{File.join(@dirs)}\/#{outputfile}\""
end

Given /^timeout is increased by (.*) seconds$/ do |seconds|
	if @aruba_timeout_seconds  
		@aruba_timeout_seconds += seconds.to_i
	else
		puts "aruba_timeout_seconds is NIL!"
	end
end

Given /^timeout is decreased by (.*) seconds$/ do |seconds|
	if @aruba_timeout_seconds
		@aruba_timeout_seconds -= seconds.to_i
	else
		puts "aruba_timeout_seconds is NIL!"
	end
end

