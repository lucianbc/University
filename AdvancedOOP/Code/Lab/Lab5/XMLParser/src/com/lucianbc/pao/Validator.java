package com.lucianbc.pao;

import java.util.ArrayDeque;
import java.util.Deque;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

class Validator {
    private Pattern pattern = Pattern.compile("<(/?)(.+?)>");

    boolean validate(String text) {
        Deque<String> tags = new ArrayDeque<>();

        Matcher matcher = pattern.matcher(text);
        while (matcher.find()) {
            if (matcher.group(1).equals("")) {   //is opening tag
                tags.addFirst(matcher.group(2));
            } else {
                String p = tags.pollFirst();
                if (!matcher.group(2).equals(p)) return false;
            }
        }
        return tags.size() == 0;
    }
}
